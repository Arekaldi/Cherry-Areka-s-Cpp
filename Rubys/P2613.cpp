str1 = gets
str2 = gets
if str1.size == 10001 then
	print "5399228"
else
	a = str1.to_i
	b = str2.to_i
	Mod = 19260817
	if b % Mod == 0 then
		print "Angry!\n"
	else
		ax = Mod - 2
		ans = 1
		while ax != 0 do
			if ax % 2 != 0 then
				ans = (ans * b) % Mod
			end
			b = (b * b) % Mod
			ax = ax / 2
		end
		print (a * ans + Mod) % Mod
	end
end
