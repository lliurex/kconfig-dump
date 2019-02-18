/*
    kconfig dump

    Copyright (C) 2019  Enrique Medina Gremaldos <quiqueiii@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <KConfig>
#include <KConfigGroup>

#include <iostream>
#include <vector>

using namespace std;

void follow(KConfigGroup group,vector<QString>& path)
{
    if (!group.exists()) {
        return;
    }
    path.push_back(group.name());
    
    QStringList keys = group.keyList();
    
    if (keys.size()>0) {
        cout<<endl;
        for (int n=1;n<path.size();n++) {
            cout<<"["<<path[n].toLocal8Bit().constData()<<"]";
        }
        cout<<endl;
        
        for (int n=0;n<keys.size();n++) {
            QString value = group.readEntry(keys.at(n));
            cout<<keys.at(n).toLocal8Bit().constData()<<"="<<value.toLocal8Bit().constData()<<endl;
        }

    }
    
    QStringList list = group.groupList();
    
    for (int n=0;n<list.size();n++) {
        KConfigGroup child = group.group(list.at(n));
        follow(child,path);
    }
    
    path.pop_back();
}

int main(int argc,char* argv[])
{
    
    if (argc<2) {
        cerr<<"missing input file"<<endl;
        exit(0);
    }
    
    vector<QString> path;
    
    QString file=argv[1];
    KConfig config(file,KConfig::OpenFlag::NoGlobals);
    path.push_back(file);
    
    QStringList list = config.groupList();
    
    for (int n=0;n<list.size();n++) {
        KConfigGroup group = config.group(list.at(n));
        
        follow(group,path);
    }
    
    return 0;
}