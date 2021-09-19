class Solution:
    def lengthLongestPath(self, input: str) -> int:
        stack, pathLen = [], 0
        i, n = 0, len(input)
        ans = 0
        tcount = 0
        while i < n:
            if input[i] == '\n':
                i += 1
                tcount = 0
            elif input[i] == '\t':
                start = i
                while i < n and input[i] == '\t':
                    i += 1
                tcount = i - start
                while tcount < len(stack):
                    pathLen -= stack.pop()  # 当前目录的深度小于栈的高度时，需要将栈中多余的目录出栈，长度也减少
            else:
                hasDot = False
                start = i
                while i < n and input[i] != '\n':
                    if input[i] == '.':
                        hasDot = True
                    i += 1
                while tcount < len(stack):
                    pathLen -= stack.pop()  # 当前目录的深度小于栈的高度时，需要将栈中多余的目录出栈，长度也减少
                stack.append(i - start)  # 当前文件名长度入栈
                pathLen += i - start
                if hasDot:
                    ans = max(ans, pathLen + len(stack) - 1)
        return ans

