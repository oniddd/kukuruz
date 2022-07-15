//           o
// 0 0 0 0 0 1 1 1 1 1
while (lo < hi)
{
    int mid = (lo + hi) / 2; // pod
    if (f(mid))
        hi = mid;
    else
        lo = mid + 1;
}

//         o
// 1 1 1 1 1 0 0 0 0 0 0
while (lo < hi)
{
    int mid = (lo + hi + 1) / 2; // strop
    if (f(mid))
        lo = mid;
    else
        hi = mid - 1;
}

// rj je u lo
