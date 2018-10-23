
void removeOdds(vector<int>& v)
{
    vector<int>::iterator p = v.begin();
    vector<int>::iterator q;
    for (;p != v.end(); p++)
        if (*p%2 != 0)
        {
            p = v.erase(p);
            p--;
        }
}
