import collections

class Solution:
    def findSubstringInWraproundString(self, p: str) -> int:
        p = '^' + p
        len_mapper = collections.defaultdict(lambda: 0)
        w = 1
        for i in range(1, len(p)):
            if ord(p[i]) - ord(p[i - 1]) == 1 or ord(p[i]) - ord(
                    p[i - 1]) == -25:
                w += 1
            else:
                w = 1
            len_mapper[p[i]] = max(len_mapper[p[i]], w)
        return sum(len_mapper.values())
