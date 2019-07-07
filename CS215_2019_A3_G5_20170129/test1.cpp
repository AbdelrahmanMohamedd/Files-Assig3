///   ///////////////   //             //    //
///   //                //                   //                                  /////////////
///   //                //             //    //                                  //         //
///   //                //             //    //                                  //         //
///   //////////////    ///////////    //    /////////////      ////////////     /////////////
///               //    //       //    //    //         //      //        //     //
///               //    //       //    //    //         //      //        //     //
///               //    //       //    //    //         //      ////////////     //
///   //////////////    //       //    //    //         //                  //   //
#include<iostream>
#include<bits/stdc++.h>
using namespace std ;


struct course
{
    char ID[6] ;///primary key
    string name ;
    string instructor_name ;
    short weeks ;
};


struct searched
{
    bool founded ;
    string position ;
};

struct index
{
    string first ;
    string second ;
};


string binarySearch(vector<index> v, int l, int r, string x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;

        // If the element is present at the middle
        // itself
        if (v[mid].first == x)
        {
             return v[mid].second ;
        }


        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (v[mid].first > x)
            return binarySearch(v, l, mid - 1, x);

        // Else the element can only be present
        // in right subarray
        return binarySearch(v, mid + 1, r, x);
    }

    // We reach here when element is not
    // present in array
    return "null";
}


void print_my_vector (vector<index> v)
{
    vector<index>::iterator it ;
    for(it = v.begin() ; it != v.end() ; it++)
    {
            cout << "first = " << it->first << " # second = " << it->second << endl ;
            //f << it->first << "=" << it->second << "|^" ;
    }
}

vector<index> get_vector(string str1)///works with pk and fk
{

    fstream f ;
    f.open(str1,ios::out|ios::in);///file , normal mode

    vector<index> v ;
    while(!f.eof())
    {
        char ch ;
        string line = "" ;
        index NEW ;
        getline(f,line,'=');
        NEW.first = line ;
        getline(f,line,'|');
        NEW.second = line ;
        f.get(ch);
        v.push_back(NEW);
    }

    v.pop_back();///delete null index from the end

    f.close();

    return v ;
}


bool compareIndex(index i1, index i2)
{
    return (i1.first < i2.first);
}


void sort_vector(vector<index> &v)
{
    sort(v.begin(),v.end(),compareIndex);
}


void print_vector(vector<index> v , string str1)
{

    fstream f ;
    f.open(str1,ios::out|ios::trunc);///index_file , trunc mode

    vector<index>::iterator it ;
    for(it = v.begin() ; it != v.end() ; it++)
    {
                        f << it->first << "=" << it->second << "|^" ;
    }

    f.close();
}


void sort_file(string str1)
{

    vector<index> v = get_vector(str1);///take the file into vector
    sort_vector(v);///sort the vector
    print_vector(v,str1);///print the vector in the file

}


void print_all(string str1)
{
    fstream f ;
    f.open(str1,ios::out|ios::in);///file , normal mode

    cout << endl << endl ;
    string line = "" ;
    while(!f.eof())
    {
        getline(f,line,'^');
        cout << line << endl ;
    }

    f.close();
}

void print_all_files(string str1,string str2,string str3)
{
    cout << endl << "/////////////////" << str1 << "/////////////////" << endl ;
    print_all(str1);
    cout << endl << "/////////////////" << str2 << "/////////////////" << endl ;
    print_all(str2);
    cout << endl << "/////////////////" << str3 << "/////////////////" << endl ;
    print_all(str3);
}


searched searching(string str1 , string attribute , string value)
{

    fstream f ;
    f.open(str1,ios::out|ios::in);///file , normal mode

    string a , b , c ;
    char ch ;
    searched s ;
    s.position = f.tellg() ;

    while(!f.eof())
    {
        getline(f,a,'=');
        if (a==attribute)// attribute founded ,
        {
               getline(f,b,'|');
               if(b==value)// value founded ,
               {
                   cout << endl << attribute << " found !!!" << endl ;
                   //cout << "value founded ,position is " << s.position << endl ;
                   s.founded = true ;
                   return s ;
               }
               else// value not founded ,
               {
                  getline(f,c,'^');
                  s.position = f.tellg() ;
               }
        }
        else //attribute not founded ,
        {
             getline(f,c,'|');
             f.get(ch);
             if(ch!='^')
             {
                    f.seekg(-1,ios::cur);
             }
             if(f.tellg()==-1)
                break;
        }

    }

    cout << endl << attribute << " not found !!!" << endl ;
    s.position = f.tellg() ;
    s.founded = false ;
    f.close();
    return s ;
}


searched binary_search_on_file(string str1 , string value)
{
 vector<index> v = get_vector(str1);///take the file into vector , already sorted
 //print_my_vector(v);

 string temp = binarySearch(v,0,v.size()-1,value) ;///binary search on the vector
 //cout << endl << "temp = " << temp << endl << endl ;

 ///take the output in searched and return it
 searched s ;
 s.founded = false ;

 if (temp != "null")
 {
     s.founded = true ;
 }

 s.position = temp ;

 return s ;
}


void print_course(string str1 , string str2 ,string str3, string attribute , string value)
{

    fstream f ;
    f.open(str1,ios::out|ios::in);///file , normal mode

   ///<new>

    searched q ;

    if(attribute=="ID")
    {
      //cout << "nigga 1" << endl ;
      q = binary_search_on_file(str2,value);///PK file
      //cout << "q.position = " << q.position << endl ;
    }


    else if (attribute=="instructor_name")
    {
      q = binary_search_on_file(str3,value);///FK file

      q = binary_search_on_file(str2,q.position);///PK file
    }

   ///</new>

    //searched q = searching(f,attribute,value);
    if (q.founded==true)
    {
      ///<important>

      int new_temp ;
      //new_temp = stoi(temp);
      istringstream iss (q.position);
      iss >> new_temp;



     f.seekg(new_temp,ios::beg);
     ///</important>
     cout << "course founded !!!" << endl ;
     //cout << "position in book : " << f.tellg() << endl ;
     string str ;
     getline(f,str,'^');
     cout << endl << str << endl ;
    }
    else
    {
     cout << "course not founded !!!" << endl ;
    }


    f.close();

}


void refresh(string str1,string str2,string str3)
{
    /*for PK file*/
    fstream f ;
    f.open(str1,ios::out|ios::in);///file , normal mode


    ///make a vector to store the information of the main file
    vector<index> v ;
    while(!f.eof())
    {
        index NEW ;
        string line = "" ;
        //int to string

        int temp = f.tellg() ;
        stringstream ss;
        ss << temp;
        NEW.second = ss.str();

        getline(f,line,'=');
        getline(f,line,'|');
        NEW.first = line ;
        getline(f,line,'^');
        v.push_back(NEW);
    }

    v.pop_back();///delete null index from the end

    ///sort the vector
    sort_vector(v);
    //print_my_vector(v);

    ///print the vector on the second file
    print_vector(v,str2);

    f.close();


    /*for fk file*/
    f.open(str1,ios::out|ios::in);///file , normal mode


    ///make a vector to store the information of the main file
    vector<index> v1 ;
    while(!f.eof())
    {
        index NEW ;
        string line = "" ;
        //int to string
        getline(f,line,'=');
        getline(f,line,'|');
        NEW.second = line ;
        getline(f,line,'|');
        getline(f,line,'=');
        getline(f,line,'|');
        NEW.first = line ;
        getline(f,line,'^');
        v1.push_back(NEW);
    }

    v1.pop_back();///delete null index from the end

    ///sort the vector
    sort_vector(v1);
    //print_my_vector(v1);

    ///print the vector on the second file
    print_vector(v1,str3);

    f.close();

}


void add_courses(string str1 , string str2 , string str3 , int a)
{

    fstream f , f_pk ;
    f.open(str1,ios::out|ios::app);///file , append mode


    course c[a] ;

    for(int i = 0 ; i < a ; i++)
    {
     cout << endl;
     f.seekg(0,ios::end);
     int pk_offset = f.tellg() ;

     ///myfile
     f << "ID=" ;               cout << "enter course #" << i+1 << " ID :" ;                  cin >> c[i].ID ;                      f << c[i].ID << "|" ; cin.ignore();
     f << "name=" ;             cout << "enter course #" << i+1 << " name :" ;                getline(cin,c[i].name) ;              f << c[i].name << "|" ;
     f << "instructor_name=" ;  cout << "enter course #" << i+1 << " instructor_name :" ;     getline(cin,c[i].instructor_name) ;   f << c[i].instructor_name << "|" ; ;
     f << "weeks=" ;            cout << "enter course #" << i+1 << " weeks :" ;               cin >> c[i].weeks ;                   f << c[i].weeks << "|" ;
     f << "^" ;

    }

    f.close();


    if(str1=="myfile.txt")
    {
     refresh(str1,str2,str3);
    }

}


bool delete_course(string str1 , string str2 , string str3 , string attribute , string value)
{

    bool w = false ;

    fstream f ;
    f.open(str1,ios::out|ios::in);///file , normal mode

    ///<new>

    searched q ;

    if(attribute=="ID")
    {
      q = binary_search_on_file(str2,value);///PK file
    }


    else if (attribute=="instructor_name")
    {

      q = binary_search_on_file(str3,value);///FK file

      q = binary_search_on_file(str2,q.position);///PK file

      if(q.founded==true)
      {
          w = true ;
      }

    }


    ///</new>


    ///delete from the file
    if (q.founded==true)
    {
     cout << "course founded !!!" << endl ;
     f.seekg(0,ios::end);
     int SIZE = f.tellg() ;


     char first[SIZE] ;/// char or string
     f.seekg(0,ios::beg);

      ///<important>

      int new_temp ;
      //new_temp = stoi(temp);
      istringstream iss (q.position);
      iss >> new_temp;

     ///</important>




     if (new_temp!=0)
     {
         f.getline(first,new_temp) ;///getline or read
         strcat(first,"^");
     }
     else
     {
         strcpy(first,"");
     }
     //cout << "first :" << first << endl ;


     f.clear();


     //cout << "tellg =" << f.tellg() << endl ;


     f.seekg(new_temp,ios::beg);
     string deleted ;///char or string
     getline(f,deleted,'^');///getline
     //cout << "deleted :" << deleted << endl ;


     //cout << "tellg =" << f.tellg() << endl ;


     char second[SIZE-f.tellg()+1] ;///char or string
     f.getline(second,SIZE-f.tellg()+1) ;///getline or read
     //cout << "second :" << second << endl ;


     strcat(first,second);
     //cout << "final : " << first << endl ;

     fstream write_file ;
     write_file.open(str1,ios::trunc|ios::out);
     write_file << first ;
     write_file.close();
     cout << endl << "course have been deleted successfully" << endl ;

    }

    else
    {
     cout << "course not founded !!!" << endl ;
    }


    if(str1=="myfile.txt")
    {
     refresh(str1,str2,str3);
    }


    f.close();


    return w ;

}

void update_course(string str1 , string str2 , string str3 , string attribute , string value)
{


    fstream f ;
    f.open(str1,ios::out|ios::in);///file , normal mode

    ///<new>

    searched q ;

    if(attribute=="ID")
    {
      q = binary_search_on_file(str2,value);///PK file
    }


    else if (attribute=="instructor_name")
    {
      q = binary_search_on_file(str3,value);///FK file

      q = binary_search_on_file(str2,q.position);///PK file
    }


    ///</new>




    if (q.founded==true)
    {

     cout << "course founded !!!" << endl ;
     f.seekg(0,ios::end);
     int SIZE = f.tellg() ;


     char first[SIZE] ;/// char or string
     f.seekg(0,ios::beg);


     ///<important>

      int new_temp ;
      //new_temp = stoi(temp);
      istringstream iss (q.position);
      iss >> new_temp;

     ///</important>


     if (new_temp!=0)
     {
         f.getline(first,new_temp) ;///getline or read
         strcat(first,"^");
     }
     else
     {
         strcpy(first,"");
     }
     //cout << "first :" << first << endl ;


     f.clear();


     //cout << "tellg =" << f.tellg() << endl ;


     f.seekg(new_temp,ios::beg);
     string deleted ;///char or string
     getline(f,deleted,'^');///getline
     //cout << "deleted :" << deleted << endl ;


     //cout << "tellg =" << f.tellg() << endl ;


     char second[SIZE-f.tellg()+1] ;///char or string
     f.getline(second,SIZE-f.tellg()+1) ;///getline or read
     //cout << "second :" << second << endl ;


     //cout << "final : " << first << endl ;

     fstream write_file ;
     write_file.open("myfile.txt",ios::trunc|ios::out);
     write_file << first ;
     course c ;
     cout << endl;
     write_file << "ID=" ;               cout << "enter course ID :" ;                  cin >> c.ID ;                      write_file << c.ID << "|" ; cin.ignore();
     write_file << "name=" ;             cout << "enter course name :" ;                getline(cin,c.name) ;              write_file << c.name << "|" ;
     write_file << "instructor_name=" ;  cout << "enter course instructor_name :" ;     getline(cin,c.instructor_name) ;   write_file << c.instructor_name << "|" ; ;
     write_file << "weeks=" ;            cout << "enter course weeks :" ;               cin >> c.weeks ;                   write_file << c.weeks << "|" ;
     write_file << "^" ;
     write_file << second ;
     write_file.close();
     cout << endl << "course have been updated successfully" ;

    }

    else
    {
     cout << "course not founded !!!" << endl ;
    }


    if(str1=="myfile.txt")
    {
     refresh(str1,str2,str3);
    }


    f.close();
}


int main()
{

    cout << "welcome to our program , this is a program to write and read books using files , enjoy it :)" << endl ;

    bool w = true ;

    int x ;

    string file = "myfile.txt" , pk_file = "pk_index.txt" , fk_file = "fk_index.txt" ;


    while(w)
    {
        fstream f ;
        f.open("flag.txt",ios::in|ios::out);
        char ch ;
        f.get(ch);
        if(ch=='0')
        {
            cout << endl << "files are not up-to-date" << endl ;
            refresh(file,pk_file,fk_file);///update the files
            f.seekp(0,ios::beg);
            f << "1" ;
            cout << endl << "refresh done , now files are up to date" << endl ;
        }



        cout << endl << endl << endl ;
        cout << "1-add course to the file" << endl
             << "2-delete course from the file" << endl
             << "3-update course details from the file" << endl
             << "4-print course from the file" << endl
             << "5-print all the courses from the files" << endl///done
             << "0-exit from the program" << endl ;///done


        cout << endl << "select the operation by input its number : " ;


        cin >> x ;


        f.seekp(0,ios::beg);
        f << "0" ;
        f.close();

        switch(x)
        {

             case 1 : //done
                    {
                        int n ;
                        cout << endl << "enter how many courses you want to add : " ;
                        cin >> n ;
                        add_courses(file,pk_file,fk_file,n);
                        sort_file(pk_file);
                        cout << endl << n << " courses have been added successfully" ;
                        break ;
                    }



             case 2 : //done
                    {
                       string attr , val ;
                       cout << endl << "what attribute would you like to use to search ? [ID,instructor_name]  : " ;
                       cin >> attr ;
                       cout << "great , enter the " << attr << " of the course : " ;
                       cin.ignore();
                       getline(cin,val);
                       bool y = delete_course(file,pk_file,fk_file,attr,val);
                       while(y==true)
                       {
                           y = delete_course(file,pk_file,fk_file,attr,val);
                       }
                       break ;
                    }

             case 3 : //done
                    {
                       string attr , val ;
                       cout << endl << "what attribute would you like to use to search ? [ID,instructor_name]  : " ;
                       cin >> attr ;
                       cout << "great , enter the " << attr << " of the course : " ;
                       cin.ignore();
                       getline(cin,val);
                       update_course(file,pk_file,fk_file,attr,val);
                       break ;
                    }




             case 4 : //done
                    {
                       string attr , val ;
                       cout << endl << "what attribute would you like to use to search ? [ID,instructor_name]  : " ;
                       cin >> attr ;
                       cout << "great , enter the " << attr << " of the course : " ;
                       cin.ignore();
                       getline(cin,val);
                       print_course(file,pk_file,fk_file,attr,val);
                       break ;
                    }



             case 5 : ///done_nigga
                    {
                       print_all_files(file,pk_file,fk_file);
                       break ;
                    }






             case 0 : ///done_nigga
                 cout << endl << "thank you for using our program :)" << endl ;
                 w = false ;
                 break;

        }



        //cout << 1/0 << endl ;

        f.open("flag.txt",ios::in|ios::out);
        f.seekp(0,ios::beg);
        f << "1" ;
        f.close();

        }



   return 0 ;
}



