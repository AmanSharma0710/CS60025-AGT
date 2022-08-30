/*
Aman Sharma
20CS30063

Compile the code using
************g++ AGT_A1_20CS30063.cpp************
Make sure the directory contains a.out, input.gbt and rapidxml.hpp
Run the generated a.out and give input file name as input.gbt when prompted by the code
************./a.out************
*/
#include<bits/stdc++.h>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

xml_document<> doc;
xml_node<> * root_node = NULL;
vector<vector<int> > vwdse;

deque<int> curtempnew;

void vdsepr(int level,int n)
{
    if(level==n)
    {
        deque<int> curtempnew1=curtempnew;

        cout<<"(";
        for(int i=0;i<n;i++)
        {
            cout<<curtempnew1.front()+1<<",)"[i==(n-1)];
            curtempnew1.pop_front();
        }
        cout<<endl;
        return;
    }

    for(int i=0;i<vwdse[level].size();i++)
    {
        curtempnew.push_back(vwdse[level][i]);
        vdsepr(level+1,n);
        curtempnew.pop_front();
    }

}

int main()
{
    string filename;
    cout << "Enter the name of the .gbt file: ";
    cin >> filename;
    ifstream theFile(filename);    //opening the file
    //READING AND PARSING THE GBT FILE
    cout << "Staring the parsing of the GBT file...\n" << setprecision(10);
    // Read the file into a buffer
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');
    // Parse the buffer
    doc.parse<0>(&buffer[0]);

    root_node = doc.first_node();

    xml_node<> *main_data_node = root_node->first_node();

    while(strcmp(main_data_node->name(), "game")!=0 && main_data_node!=doc.last_node())
    {
        main_data_node = main_data_node->next_sibling();
    }
    //We step inside game to get to the nfgfile node
    main_data_node = main_data_node->first_node();
    string data = main_data_node->value();
    string name_of_game = "";
    int nplayers = 0;
    int i = 0;
    
    while(data[i]!='"'){
        i++;
    }
    i++;
    while(data[i]!='"'){
        name_of_game += data[i];
        i++;
    }
    
    for(; data[i]!='{'; i++)
    {
        continue;
    }
    for(; data[i]!='}'; i++)
    {
        if(data[i]=='"')
            nplayers++;
    
    }
    nplayers/=2;
    cout<<"The name of the game is: "<<name_of_game<<endl;
    cout<<"Number of players: "<<nplayers<<endl;
    vector<int> strategies(nplayers,0);
    //We move i to the point where the first opening bracket is encountered
    while(data[i++]!='{');
    //We continue until number or right brackets is less than no of left brackets
    int left=1,right=0, str = 0;
    while(left>right)
    {
        if(data[i]=='{')
            left++;
        if(data[i]=='}'){
            if(left!=right){
                strategies[right] = str/2;
                str = 0;
            }
            right++;
        }
        if(data[i]=='"')
            str++;
        i++;
    }
    

    cout<<"Number of strategies for:"<<endl;
    for(int k = 0; k<nplayers; k++)
    {
        cout<<"Player "<<k+1<<": "<<strategies[k]<<endl;
    }
    int j, nlb, nrb;
    j = i;

    nlb = nrb = 0;

    for(; data[j]!='\0'; j++)
    {
        if(data[j]=='{')
        {
            nlb++;
            j++;
            break;
        }
    }

    for(;nlb!=nrb; j++)
    {
        if(data[j]=='{')
        {
            nlb++;
        }

        if(data[j]=='}')
        {
            nrb++;
            j++;
        }
    }

    int totalstrategies = 1;
    for(int k = 0; k<nplayers; k++)
    {
        totalstrategies*=strategies[k];
    }
    vector<int> lines(totalstrategies,0);
        

    int k = 0;

    for(; data[j]!='\0'; j++)
    {
        if(data[j]>='0'&& data[j]<='9')
        {
            lines[k] = lines[k]*10 + data[j]-'0';
        }

        if(data[j]==' ')
            k++;
    }
    int y = 0;

    for(k = 0; k<totalstrategies; k++)
    {
        cout<<lines[k]<<endl;
    }

    nlb = nrb = 0;
    vector<vector<int> > mat;
    vector<int> row;

    for(; data[i]!='{'; i++)
    {
        continue;
    }

    i++;
    nlb++;

    int index1 =0, index2 = 0;//mat[index1][index2]

    for(; nlb!=nrb; i++)
    {
        if(data[i]=='{')
        {
            nlb++;
            mat.push_back(row);
        }
        if(data[i]=='}')
        {
            nrb++;
            index1++;
            index2 = 0;
        }

        if(data[i]>='0'&&data[i]<='9')
        {
            if(data[i-1]>='0'&& data[i-1]<='9')
            {
                if(mat[index1][index2]<0)
                {
                    mat[index1][index2] = mat[index1][index2]*10 - data[i]-'0';
                }
                else
                {
                    mat[index1][index2] = mat[index1][index2]*10 + data[i]-'0';
                }
                
            }
            else
            {
                if(data[i-1]=='-')
                {
                    mat[index1].push_back(-1*(data[i]-'0'));
                }
                else
                {
                    mat[index1].push_back(data[i]-'0');
                }
                
                index2++;
            }
        }
    }
    cout<<"check"<<endl;

    vector<vector<int> > finalmat;
    for(k = 0; k<totalstrategies; k++)
    {
        finalmat.push_back(mat[lines[k]-1]);
    }

    for(k = 0; k<totalstrategies; k++)
    {
        for(y = 0; y<nplayers; y++)
        {
            cout<<finalmat[k][y]<<" ";
        }
        cout<<endl;
    }

    //skip

    vector<int> sdse;
    vector<int> wdse;

    int n=nplayers;
    int m=totalstrategies;
    m=strategies[0];

    cout<<"Variables n and m"<<" "<<n<<" "<<m<<endl;

    


    for(int p=0;p<n;p++)
    {
        set<int> s;
        set<int>::iterator it1;
        set<int>::iterator it2;
        vector<int> vtemp(m,0);

        int st=1;
        int wek=1;
        
        for(int i=0;i<pow(m,n);i++)
        {
            s.insert(i);
        }

        for(int i=0;i<pow(m,n-1);i++)
        {
            vector<int> temptemp;

            it1=s.begin();
            int temp=(*it1);

            int maxv=-100000;
            int maxind=-1;

            for(int l=0;l<m;l++)
            {
                if(maxv==finalmat[temp][p])
                {
                    temptemp.push_back(l);
                }

                if(maxv<finalmat[temp][p])
                {
                    maxv=finalmat[temp][p];
                    maxind=l;
                    temptemp.clear();
                    temptemp.push_back(l);
                }

                s.erase(s.find(temp));
                temp=temp+pow(m,p);
                
            }

            if(temptemp.size()>1)
            {
                for(int j=0;j<temptemp.size();j++) vtemp[temptemp[j]]++;

                vtemp[maxind]--;

                st=0;

                //if(temptemp.size()==1)

            }

            

            vtemp[maxind]++;

        }

        int tempval=-1;

        for(int i=0;i<m;i++)
        {
            if(vtemp[i]==pow(m,n-1))
            {
                tempval=i;
            }
        }

        int maxcur=-1;

        vector<int> vwp;

        for(int i=0;i<m;i++)
        {
            if(vtemp[i]>maxcur && vtemp[i]>=pow(m,n-1))
            {
                tempval=i;
                maxcur=vtemp[i];
            }
            if(vtemp[i]==maxcur)
            {
                vwp.push_back(i);
            }
        }

        //tempval=maxcur;

        int vwst=0;

        if(vwp.size()>1)
        {
            //vwst=0;
            tempval=-1;

        }
        else if(vwp.size()!=1)
        {
            vector<int> newtemp;
            newtemp.push_back(-1);
            vwdse.push_back(newtemp);
            vwst=1;
        }

        wdse.push_back(tempval);

        if(vwst==0)
        {
            vector<int> newtemp;
            newtemp.push_back(tempval);
            vwdse.push_back(newtemp);
        }


        if(st==0)
        {
            tempval=-1;
        }
        sdse.push_back(tempval);

    }

    cout<<"Best SDS for each player if exists:"<<endl;

    for(int i=0;i<n;i++)
    {
        cout<<"For player "<<i+1;
        if(sdse[i]!=-1) cout<<": Strategy number: "<<sdse[i]+1<<endl;
        else cout<<": Does not exist"<<endl;
    }
    cout<<endl<<endl;


    cout<<"Best WDS for each player if exists:"<<endl;

    for(int i=0;i<n;i++)
    {
        cout<<"For player "<<i+1;
        if(wdse[i]!=-1) cout<<": Strategy number: "<<wdse[i]+1<<endl;
        else cout<<": Does not exist"<<endl;
    }
    cout<<endl<<endl;

    cout<<"Best VWDS for each player if exists:"<<endl;

    for(int i=0;i<n;i++)
    {
        cout<<"For player number: "<<i+1<<" following strategy numbers: ";
        for(int j=0;j<vwdse[i].size();j++)
        {
            cout<<vwdse[i][j]+1<<" ";
        }
        cout<<endl;
    }
    cout<<endl;


    bool stb=1;

    for(int i=0;i<n;i++)
    {
        if(sdse[i]==-1) stb=0;
    }

    if(stb)
    {
        cout<<"Yes, SDSE exists at strategy (";
        for(int i=0;i<n;i++)
        {
            cout<<sdse[i]+1<<",)"[i==n-1];
        }
        cout<<endl;
    }
    else
    {
        cout<<"No SDSE"<<endl;
    }


    stb=1;

    for(int i=0;i<n;i++)
    {
        if(wdse[i]==-1) stb=0;
    }

    if(stb)
    {
        cout<<"Yes, WDSE exists at strategy (";
        for(int i=0;i<n;i++)
        {
            cout<<wdse[i]+1<<",)"[i==n-1];
        }
        cout<<endl;
    }
    else
    {
        cout<<"No WDSE"<<endl;
    }


    stb=1;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<vwdse[i].size();j++) if(vwdse[i][j]==-1) stb=0;
    }

    if(stb)
    {
        cout<<"Yes, VWDSE exists at straties: ";
        vdsepr(0,n);
        cout<<endl;
    }
    else
    {
        cout<<"No VWDSE"<<endl;
    }



    cout<<endl;

    return 0;
}

