n = Integer(gets)
is_locked = false
# 开始并未上锁
ans = "blue"
# 答案初始为 "blue"
while n > 0 do
    str1 = gets
    if str1[0] == 'l' and str1[1] == 'o' then
        is_locked = true
        # 判断是否为 lock
    else
        if str1[0] == 'u' and str1[1] == 'n' then
            is_locked = false
            # 判断是否为 unlock
        else
            if is_locked == false then
                ans = str1
                # 将答案更改
            end
        end
    end
    # 注意这里的 end 嵌套
    n = n - 1
    # 将 n 减一
end