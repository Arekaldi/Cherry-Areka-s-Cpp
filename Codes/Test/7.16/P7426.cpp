#include <bits/stdc++.h>

using namespace std;

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

const int maxm = 2e6 + 1, maxn = 4e5 + 1;
#define int long long

int Month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Student {
	public:
		int num; //离散化后的编号 
		long long id; //学号 
		bool sex; //性别 
		int Pes; //体育专项成绩 
		int mit, sed; //长跑分，秒
		bool pass; //是否通过体育测试
		int Pef; // 期末成绩
		int c; //参加班级训练营的次数 
		int cnt; //阳光长跑合格次数 
		int g1, g2;
		inline bool operator < (const Student a) const {
			return a.id > id;
		}
};


class Sun_Running {
	public:
		int mon, dy; //月、日
		long long id; //学号
		int shr, smit, ssed; //开始时，分，秒 
		int ehr, emit, esed; //结束时，分，秒 
		double ln; // 运动距离
		int spa, spb; //暂停时间
		int s; // 运动步数 
};

class Day {
	public:
		int hr, mit, sed;
		int ddy;
		//时分秒 
};

Student st[maxn];
Sun_Running rc[maxn];

vector <int> srun[maxn];
bool V[maxm];

inline int Get_Time(Day a, Day b); //得到两个时间相邻的秒数 
inline bool check0(Day a, Day b); //两天相邻，判断是否合法 
inline bool check1(Sun_Running a, Sun_Running b); // 判断 a、b 两条记录是否相差 6 小时 
inline bool check2(Sun_Running x); // 判断记录本身是否合格
inline int check3(int x, bool a); //判断长跑成绩
inline int check4(int x); //判断阳光长跑成绩
inline int check5(int x); //判断出勤等成绩 
inline int G_PE_C(Student x); // 得到体育课成绩
inline int G_Run(Student x); // 得到长跑测试成绩
inline int G_Sun_Run(Student x); // 得到阳光跑步成绩
inline int G_bd(Student x); // 得到体质测试成绩
inline int G_Fre_z(Student x); // 得到大一专项测试成绩
// Freshman! 
inline int Get_Gread(Student x); // 得到百分制成绩
inline int Get_level(Student x); // 得到等级 
inline void To_char(int x); //将等级转化为字符 
inline int Get_num(long long id); // 由 id 得到num
int n, m;

map <long long, int> M;

signed main()  {
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
	
	scanf("%lld", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &st[i].id);
		st[i].num = i;
		char x; cin >> x;
		st[i].sex = x == 'M' ? true : false;
		scanf("%lld", &st[i].Pes);
		int a1, b1;
		scanf("%lld\'%lld\"", &a1, &b1);
		st[i].mit = a1, st[i].sed = b1;
		cin >> x;
		st[i].pass = x == 'P' ? true : false;
		scanf("%lld", &st[i].Pef);
		scanf("%lld", &st[i].c);
		M[st[i].id] = i;
	}
	scanf("%lld", &m);
	for(int i = 1; i <= m; ++i) {
		string ddy;
		cin >> ddy;
		int x1 = (ddy[4] - '0') * 10 + ddy[5] - '0';
		int x2 = (ddy[6] - '0') * 10 + ddy[7] - '0';
		rc[i].mon = x1, rc[i].dy = x2;
		scanf("%lld", &rc[i].id);
		scanf("%lld:%lld:%lld", &rc[i].shr, &rc[i].smit, &rc[i].ssed);
		scanf("%lld:%lld:%lld", &rc[i].ehr, &rc[i].emit, &rc[i].esed);
		scanf("%lf", &rc[i].ln);
//		cin >> rc[i].ln;
		rc[i].ln *= 1000;
		int a1, b1;
		scanf("%lld\'%lld\"", &a1, &b1);
		rc[i].spa = a1, rc[i].spb = b1;
		scanf("%lld", &rc[i].s);
		int num = Get_num(rc[i].id);
		if(check2(rc[i]))
			srun[num].push_back(i);
	}
//	cout << srun[1].size() << endl;
//	cout << "sljd" << endl;
//	for(int i = 1; i <= m; ++i) {
//		printf("2017%d%d ", rc[i].mon, rc[i].dy);
//		printf("%d ", rc[i].id);
//		printf("%d:%d:%d ", rc[i].shr, rc[i].smit, rc[i].ssed);
//		printf("%d:%d:%d ", rc[i].ehr, rc[i].emit, rc[i].esed);
//		printf("%.2lf ", rc[i].ln);
//		cout << rc[i].spa << "\'" << rc[i].spb << "\"" << " ";
//		printf("%d\n", rc[i].s);
//	}
	sort(st + 1, st + n + 1);
	for(int i = 1; i <= n; ++i)
		st[i].cnt = G_Sun_Run(st[i]);
	
	for(int i = 1; i <= n; ++i) {
		st[i].g1 = Get_Gread(st[i]), st[i].g2 = Get_level(st[i]);
	}
	for(int i = 1; i <= n; ++i) {
//		cout << st[i].id << " " << st[i].g1 << Judge(st[i].g2);
		printf("%lld %lld ", st[i].id, st[i].g1);
		To_char(st[i].g2);
	}
}


inline int Get_num(long long id) {
	return M[id];
}

inline int Get_Time(Day a, Day b) {
	int ha = a.hr, mia = a.mit, sea = a.sed;
	int hb = b.hr, mib = b.mit, seb = b.sed;
	int ch = 0, cm = 0, cs = 0;
	//差几小时 差几分钟 差几秒 
	//先把a、b换算成整点，然后求差值
	
	int nha = ha, nhb = hb;
	int nmia = mia, nmib = mib;
	if(sea != 0) {
		nmia++;
		if(nmia == 60) {
			nha++;
			nmia = 0;
		}
		cs += 60 - sea;
		sea = 0;
	}
	if(nmia != 0)  {
		nha++;
		if(nha == 24)
			nha = 0;
		cm += 60 - nmia;
		nmia = 0;
	}
	if(a.ddy != b.ddy) {
		int x1 = 24 - nha, x2 = nhb;
		ch += (nha == 0) ? x2 : (x2 + x1);
	}
	else
		ch += (nhb - nha);
	cm += nmib;
	cs += seb;
	cm += ch * 60;
	cs += cm * 60;
	return cs;
}

inline bool check0(Day a, Day b) {
	return Get_Time(a, b) >= 21600;
}

/*
class Day {
	public:
		int hr, mit, sed;
		//时分秒 
};
*/

inline bool check1(Sun_Running a, Sun_Running b) {
	int ma = a.mon, mb = b.mon, da = a.dy, db = b.dy;
	// a、b 的年月日
	int ha = a.ehr, mia = a.emit, sea = a.esed;
	// a的结束时间
	int hb = b.shr, mib = b.smit, seb = b.ssed;
	
	if(ma < mb) {
		if(da == Month[ma] and db == 1) {
			Day x1, x2;
			x1.hr = ha, x1.mit = mia, x1.sed = sea, x1.ddy = 1;
			x2.hr = hb, x2.mit = mib, x2.sed = seb, x2.ddy = 2;
			return check0(x1, x2);
		}
		else
			return true;
	}
	if(da != db) {
		if(db != da + 1)
			return true;
		Day x1, x2;
		x1.hr = ha, x1.mit = mia, x1.sed = sea, x1.ddy = 1;
		x2.hr = hb, x2.mit = mib, x2.sed = seb, x2.ddy = 2;
		return check0(x1, x2);
	}
	else {
		if(hb - ha <= 4)
			return false;
		Day x1, x2;
		x1.hr = ha, x1.mit = mia, x1.sed = sea, x1.ddy = 1;
		x2.hr = hb, x2.mit = mib, x2.sed = seb, x2.ddy = 1;
		return check0(x1, x2);
	}
}

inline bool check2(Sun_Running x) {
	int num = Get_num(x.id);
	bool sex = st[num].sex;
	if(sex) {
		if(x.ln < 3000)
			return false;
	}
	if(!sex) {
		if(x.ln < 1500)
			return false;
	}
	Day x1, x2;
	x1.hr = x.shr, x1.mit = x.smit, x1.sed = x.ssed;
	x2.hr = x.ehr, x2.mit = x.emit, x2.sed = x.esed;
	x1.ddy = x2.ddy = 1;
	int Tsimes = Get_Time(x1, x2);
	double tmm = Tsimes;
	double v = x.ln / tmm;
	if(v < 2.0 or v > 5.0)
		return false;
	x1.hr = 0, x1.mit = 0, x1.sed = 0;
	x2.hr = 0, x2.mit = x.spa, x2.sed = x.spb;
	x1.ddy = x2.ddy = 1;
	// 计算暂停时间
	int ddd = Get_Time(x1, x2);
	if(ddd > 270)
		return false;
	double xs = x.s * 1.0;
	double xx = x.ln / xs;
	if(xx > 1.5)
		return false;
	return true;
}

inline int check3(int x, bool a) {
	// Man: 750 780 810 840 870 910 950 990 1030 1080
	if(a) {
		if(x <= 750)
			return 20;
		if(x > 750 and x <= 780)
			return 18;
		if(x > 780 and x <= 810)
			return 16;
		if(x > 810 and x <= 840)
			return 14;
		if(x > 840 and x <= 870)
			return 12;
		if(x > 870 and x <= 910)
			return 10;
		if(x > 910 and x <= 950)
			return 8;
		if(x > 950 and x <= 990)
			return 6;
		if(x > 990 and x <= 1030)
			return 4;
		if(x > 1030 and x <= 1080)
			return 2;
		if(x > 1080)
			return 0;
	}
	// Woman: 400 417 434 451 470 485 500 515 530 540
	else {
		if(x <= 400)
			return 20;
		if(x > 400 and x <= 417)
			return 18;
		if(x > 417 and x <= 434)
			return 16;
		if(x > 434 and x <= 451)
			return 14;
		if(x > 451 and x <= 470)
			return 12;
		if(x > 470 and x <= 485)
			return 10;
		if(x > 485 and x <= 500)
			return 8;
		if(x > 500 and x <= 515)
			return 6;
		if(x > 515 and x <= 530)
			return 4;
		if(x > 530 and x <= 540)
			return 2;
		if(x > 540)
			return 0;
	}
}

inline int check4(int x) {
	if(x >= 21)
		return 10;
	if(x <= 20 and x >= 19)
		return 9;
	if(x <= 18 and x >= 17)
		return 8;
	if(x <= 16 and x >= 14)
		return 7;
	if(x <= 13 and x >= 11)
		return 6;
	if(x <= 10 and x >= 7)
		return 4;
	if(x <= 6 and x >= 3)
		return 2;
	return 0;
}

inline int check5(int x) {
	if(x >= 18)
		return 5;
	if(x <= 17 and x >= 15)
		return 4;
	if(x <= 14 and x >= 12)
		return 3;
	if(x <= 11 and x >= 9)
		return 2;
	if(x <= 8 and x >= 6)
		return 1;
	return 0;
}

inline int G_PE_C(Student x) {
	return x.Pes;
}

inline int G_Run(Student x) {
	Day x1, x2;
	x1.hr = 0, x1.mit = 0, x1.sed = 0;
	x2.hr = 0, x2.mit = x.mit, x2.sed = x.sed;
	x1.ddy = x2.ddy = 1;
	int T = Get_Time(x1, x2);
	return check3(T, x.sex);
}

inline int G_Sun_Run(Student x) {
	int cnt = 0, num = Get_num(x.id);
	if(srun[num].size() == 0)
		return 0;
//	if(num == 161)
//		cout << srun[161].size() << endl;
//	for(int i = 0; i < srun[num].size() - 1; ++i) {
//		int j = i + 1;
//		if(check1(rc[srun[num][i]], rc[srun[num][j]])) {
//			cnt++;
//			if(num == 8)
//				cout << i << " " << j << endl;
//		}
//		else {
//			bool flag = false;
//			int k;
//			for(k = j + 1; k < srun[num].size(); ++k) {
//				if(check1(rc[srun[num][i]], rc[srun[num][k]]))
//					break;
//				if(k == srun[num].size() - 1) {
//					flag = true;
//					break;
//				}
//			}
//			if(flag) {
//				break;
//			}
//			else {
//				if(num == 8)
//					cout << i << " " << k << endl;
//				i = k - 1, cnt++;
//			}
//		}
//	}
	memset(V, 0, sizeof(V));
	V[0] = true;
//	if(num == 455) {
//		cout << srun[num].size() << endl;
////		cout << 0 << endl;
//		for(int j = 0; j < srun[num].size(); ++j) {
//			int i = srun[num][j];
//			printf("2017%d%d ", rc[i].mon, rc[i].dy);
//			printf("%d ", rc[i].id);
//			printf("%d:%d:%d ", rc[i].shr, rc[i].smit, rc[i].ssed);
//			printf("%d:%d:%d ", rc[i].ehr, rc[i].emit, rc[i].esed);
//			printf("%.2lf ", rc[i].ln);
//			cout << rc[i].spa << "\'" << rc[i].spb << "\"" << " ";
//			printf("%d\n", rc[i].s);
//		}
//	}
	for(int i = 0; i < srun[num].size() - 1; ++i) {
		int j = i + 1;
		if(check1(rc[srun[num][i]], rc[srun[num][j]])) {
			V[j] = true;
//			if(num == 455)
//				cout << j << endl;
		}
		else {
			bool flag = false;
			int k;
			for(k = j + 1; k < srun[num].size(); ++k) {
				if(check1(rc[srun[num][i]], rc[srun[num][k]]))
					break;
				if(k == srun[num].size() - 1) {
					flag = true;
					break;
				}
			}
			if(flag) {
				break;
			}
			else {
				i = k - 1, V[k] = true;
//				if(num == 455)
//					cout << k << endl;
			}
		}
	}
	
	for(int i = 0; i < srun[num].size(); ++i) {
		cnt += (V[i] == true);
//		if(num == 455) {
//			cout << i << " " << V[i] << " " << cnt << endl;
//		}
	}
//	if(num == 455) {
//		cout << cnt << endl;
//	}
	return cnt;
}

inline int G_bd(Student x) {
	if(x.pass)
		return 10;
	else
		return 0;
}

inline int G_Fre_z(Student x) {
	int chu = x.cnt + x.c;
//	if(x.num == 874) {
//		cout << x.cnt << endl;
//	}
	return check5(chu) + x.Pef;
}

inline int Get_Gread(Student x) {
//inline int G_PE_C(Student x); // 得到体育课成绩
//inline int G_Run(Student x); // 得到长跑测试成绩
//inline int G_Sun_Run(Student x); // 得到阳光跑步成绩
//inline int G_bd(Student x); // 得到体质测试成绩
//inline int G_Fre_z(Student x); // 得到大一专项测试成绩
	int a = G_PE_C(x), b = G_Run(x), c = check4(x.cnt), d = G_bd(x), e = G_Fre_z(x);
//	cout << x.id << " " << a << " " << b << " " << c << " " << d << " " << e << endl;
	return a + b + c + d + e;
}

inline int Get_level(Student x) {
	int g = x.g1;
	int p;
	if(g <= 100 and g >= 95)
		p = 1;
	else if(g < 95 and g >= 90)
		p = 2;
	else if(g < 90 and g >= 85)
		p = 3;
	else if(g < 85 and g >= 80)
		p = 4;
	else if(g < 80 and g >= 77)
		p = 5;
	else if(g < 77 and g >= 73)
		p = 6;
	else if(g < 73 and g >= 70)
		p = 7;
	else if(g < 70 and g >= 67)
		p = 8;
	else if(g < 67 and g >= 63)
		p = 9;
	else if(g < 63 and g >= 60)
		p = 10;
	else
		p = 11;
	return p;
}

inline void To_char(int x) {
	if(x == 1)
		puts("A");
	if(x == 2)
		puts("A-");
	if(x == 3)
		puts("B+");
	if(x == 4)
		puts("B");
	if(x == 5)
		puts("B-");
	if(x == 6)
		puts("C+");
	if(x == 7)
		puts("C");
	if(x == 8)
		puts("C-");
	if(x == 9)
		puts("D+");
	if(x == 10)
		puts("D");
	if(x == 11)
		puts("F");
}

/*
class Sun_Running {
	public:
		int mon, dy; //月、日
		long long id; //学号
		int shr, smit, ssed; //开始时，分，秒 
		int ehr, emit, esed; //结束时，分，秒 
		double ln; // 运动距离
		int spa, spb; //暂停时间
		int s; // 运动步数 
};

*/

/*
class Student {
	public:
		int num; //离散化后的编号 
		long long id; //学号 
		bool sex; //性别 
		int Pes; //体育专项成绩 
		int mit, sed; //长跑分，秒
		bool pass; //是否通过体育测试
		int Pef; //期末成绩 
		int c; //参加班级训练营的次数 
		int cnt; //阳光长跑合格次数 
		int g1, g2;
		inline bool operator < (const Student a) const {
			return a.id > id;
		}
};
*/

/*
inline int Get_Time(Day a, Day b); //得到两个时间相邻的秒数 
inline bool check0(Day a, Day b); //两天相邻，判断是否合法 
inline bool check1(Sun_Running a, Sun_Running b); // 判断 a、b 两条记录是否相差 6 小时 
inline bool check2(Sun_Running x); // 判断记录本身是否合格
inline int check3(int x, bool a); //判断长跑成绩
inline int check4(int x); //判断阳光长跑成绩
inline int check5(int x); //判断出勤等成绩 
inline int G_PE_C(Student x); // 得到体育课成绩
inline int G_Run(Student x); // 得到长跑测试成绩
inline int G_Sun_Run(Student x); // 得到阳光跑步成绩
inline int G_bd(Student x); // 得到体质测试成绩
inline int G_Fre_z(Student x); // 得到大一专项测试成绩
// Freshman! 
inline int Get_Gread(Student x); // 得到百分制成绩
inline int Get_level(Student x); // 得到等级 
inline char To_char(int x); //将等级转化为字符 
inline int Get_num(long long id); // 由 id 得到num
*/

/*

		int mon, dy; //月、日
		long long id; //学号
		int hr, mit, sed; //时，分，秒
		double ln; // 运动距离
		int spa, spb; //暂停时间
		int s; // 运动步数
*/
