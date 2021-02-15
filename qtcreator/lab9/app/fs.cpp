#include "fs.hpp"
vector<string> readCSV(fstream &fin)
{
    if(!fin.is_open())
    {
        cout << "ERROR" << endl;
        exit(1);
    }
    vector<string> arr;
    while(!fin.eof())
    {
        string temp;
        getline(fin,temp);
        arr.push_back(temp);
    }
    arr.erase(arr.end());
    return arr;
}
void write(fstream &fout, vector<string>& arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if(i == arr.size()-1)
        {
            fout << arr[i];
            break;
        }
        fout << arr[i] << endl;
    }
}
