class RangeModule //线段树
{
    int tr[3500000], lson[3500000], rson[3500000], cnt = 2, lazy0[3500000], lazy1[3500000];

public:
    RangeModule()
    {
    }

    void push_down(int p)
    {
        if (lson[p] == 0)
            lson[p] = cnt++;
        if (rson[p] == 0)
            rson[p] = cnt++;
        if (lazy0[p])
        {
            lazy0[lson[p]] = 1;
            lazy0[rson[p]] = 1;
            lazy1[lson[p]] = 0;
            lazy1[rson[p]] = 0;
            tr[lson[p]] = 0;
            tr[rson[p]] = 0;
            lazy0[p] = 0;
        }
        if (lazy1[p])
        {
            lazy0[lson[p]] = 0;
            lazy0[rson[p]] = 0;
            lazy1[lson[p]] = 1;
            lazy1[rson[p]] = 1;
            tr[lson[p]] = 1;
            tr[rson[p]] = 1;
            lazy1[p] = 0;
        }
    }

    void change(int p, int l, int r, int s, int t, int v)
    {
        if (r < s || l > t)
        {
            return;
        }
        else if (s <= l && r <= t)
        {
            if (v == 0)
            {
                lazy0[p] = 1;
                lazy1[p] = 0;
                tr[p] = 0;
            }
            else
            {
                lazy0[p] = 0;
                lazy1[p] = 1;
                tr[p] = 1;
            }
        }
        else
        {
            int m = l + r >> 1;
            push_down(p);
            change(lson[p], l, m, s, t, v);
            change(rson[p], m + 1, r, s, t, v);
            tr[p] = tr[lson[p]] & tr[rson[p]];
        }
    }

    int query(int p, int l, int r, int s, int t)
    {
        if (r < s || l > t)
        {
            return 1;
        }
        else if (s <= l && r <= t)
        {
            return tr[p];
        }
        else
        {
            int m = l + r >> 1;
            push_down(p);
            return query(lson[p], l, m, s, t) & query(rson[p], m + 1, r, s, t);
        }
    }

    void addRange(int left, int right)
    {
        change(1, 0, 1e9, left, right - 1, 1);
    }

    bool queryRange(int left, int right)
    {
        return query(1, 0, 1e9, left, right - 1);
    }

    void removeRange(int left, int right)
    {
        change(1, 0, 1e9, left, right - 1, 0);
    }
};
