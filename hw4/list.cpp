

void listAll(string path, const Domain* d) // two-parameter overload
{
    //You will write this code.
    if (d->label() == path && d->subdomains().size() == 0)
    {
        cout << path <<endl;
        return;
    }
    
    if (d->subdomains().size() == 0)
    {
        if (path == "")
            cout <<path << endl;
        else
            cout <<path << endl;
        return;
    }
    
    for (int k = 0; k < d->subdomains().size(); k++)
    {
        if (path == "")
        {
            listAll(d->subdomains()[k]->label()+path,d->subdomains()[k]);
        }
        else
        {
            listAll(d->subdomains()[k]->label()+"."+path,d->subdomains()[k]);
        }

    }
}
