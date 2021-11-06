/*
Author: Matthew Rozanoff

Will read a file with words and phenomes and find the identical, removed, added, and replaced words. 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <algorithm>
using namespace std;

string beforeSpace, afterSpace;

string removeLeadingSpaces(string line){
	string sansline;
	int i = 0;//starts i

	while(i < line.length() && isspace(line[i])){
		sansline += "";
		i++;

	}//using project stuff, checking spaces first, then adding normally

	while(i < line.length()){
		sansline += line[i];
		i++;

	}//adding normally

	return sansline;
}

void splitOnSpace(string s, string & before, string & after) {
  // reset strings
    before = ""; 
    after = "";
  // accumulate before space
    int i = 0;
    while (i < s.size() && not isspace(s[i])) { 
        before = before + s[i]; 
        i++; 
    }
  // skip the space
    i++;
    // accumulate after space
    while (i < s.size()) { 
        after = after + s[i]; 
        i++; 
    }
}


void findident(string word, string pronunciation){ // finding identical
	ifstream gin("cmudict.0.7a");
	if (gin.fail()) 
	{
   	 cerr << "File cannot be opened for reading." << endl;
   	 exit(1); // exit if failed to open the file
	} 
	
	string junk, pro, w;        // new string variable
	getline(gin, junk); // read one line from the file 
	cout << "Identical        :";

while(gin >> w) { 
		getline(gin, pro);
		splitOnSpace(pro, beforeSpace, afterSpace);
		
		if(afterSpace == pronunciation && w != word){	
			cout << " " << w;	
		}
	} //looking for exact phenomes
	cout << endl;
}

bool clean(string word){
	for(int i = 0; i<word.length(); i++){
		if(word[i] == '1' || word[i] == '2' || word[i] == '-' || word[i] == '%' || word[i] == '&' || word[i] == '3'){
			return false;
		}
	}
	return true;
}

int findlength(string word){
	int count = 0;
	int i = 0;
	while(i < word.length()){
		if(isspace(word[i])){
			count += 1;
		}
		i++;
	} //extra code to help format in other functions, counts the length of phenomes
	return count+1;
}


void removep(string word){ //finding removed phoneme


	ifstream gin2("cmudict.0.7a");
	if (gin2.fail()) 
	{
   	 cerr << "File cannot be opened for reading." << endl;
   	 exit(1); // exit if failed to open the file
	}
	
	string junk, pro, w, a, b, c,d,e,f,g,h,i, possible;     // new string variable
	getline(gin2, junk); // read one line from the file 

	int match = 0;


	splitOnSpace(word, beforeSpace, afterSpace);
	a = beforeSpace;

	string values[9];

	values[0] = {beforeSpace};

	for(int i = 1; i < 9; i++){
		splitOnSpace(afterSpace, beforeSpace, afterSpace);
		values[i] = {beforeSpace};
	}

	cout << "Remove phoneme   :";
	while(gin2 >> w) { 
		getline(gin2, pro);
		string fixed = removeLeadingSpaces(pro);


		//cout << findlength(fixed);
		possible = "";
		int check = 1;
		match = 0;
		int count = 0;
		if(clean(w)==true){
		splitOnSpace(fixed, beforeSpace, afterSpace);
		if(beforeSpace == a){

			possible += beforeSpace;
			
			count += 1;
			int leng = findlength(word);


			while(check < leng-1){
			//checking for word with same first letter	
				splitOnSpace(afterSpace, beforeSpace, afterSpace);
				
				if(beforeSpace == values[count] && match == 0){
					possible += " ";
					possible += beforeSpace;
					
					count += 1;
				}
				else if(beforeSpace == values[count+1]){
					possible += " ";
					possible += beforeSpace;

					count += 1;
                   
				}				
				else if(beforeSpace != values[count] && match < 1){
					match += 1;
					possible += " ";
					possible += beforeSpace;
                    count +=1;

                }

				if(match > 1){break;}
				check++;
				
			} //doing a whole new thing where we want the checking to be exact

			if(possible != word && match < 1 && check == leng-1 && findlength(fixed) == leng-1) {cout << " " << w;}
		}
		else{
			match += 1;
			possible += beforeSpace;
			
            count += 1;
			int leng = findlength(word);
            //checking word with different first letter

			while(check < leng-1){
				if(beforeSpace != values[count]){break;}//getting rid of words that dont start with the correct letter

				splitOnSpace(afterSpace, beforeSpace, afterSpace);
                
				if(beforeSpace == values[count+1]){
					possible += " ";
					possible += beforeSpace;

					count += 1;
                   
				}					
				else if(beforeSpace != values[count+1]){
					match += 1;
                }
				else if(beforeSpace != values[count]){
					match += 1;
                }
                
				if(match > 1){break;}
				check++;
				
			}
			if(check == leng-1 && match < 2 && findlength(fixed) == leng-1 && possible != word) {cout << " " << w;}
		}			
	}}
	cout << endl;
}

void addp(string word){


	ifstream gin2("cmudict.0.7a");
	if (gin2.fail()) 
	{
   	 cerr << "File cannot be opened for reading." << endl;
   	 exit(1); // exit if failed to open the file
	}
	
	string junk, pro, w, a, b, c,d,e,f,g,h,i, possible;     // new string variable
	getline(gin2, junk); // read one line from the file 

	int match = 0;


	splitOnSpace(word, beforeSpace, afterSpace);
	a = beforeSpace;

	string values[9];

	values[0] = {beforeSpace};

	for(int i = 1; i < 9; i++){
		splitOnSpace(afterSpace, beforeSpace, afterSpace);
		values[i] = {beforeSpace};
	}

	cout << "Add phoneme      :";
	while(gin2 >> w) { 
		getline(gin2, pro);
		string fixed = removeLeadingSpaces(pro);
		//cout << pro << endl;
		if(clean(w)==true){
		splitOnSpace(fixed, beforeSpace, afterSpace);

		//cout << findlength(fixed);
		possible = "";
		int check = 1;
		match = 0;
		int count = 0;
		
		if(beforeSpace == a){

			possible += beforeSpace;
			
			count += 1;
			int leng = findlength(word);


			while(check < leng+1){
				
				splitOnSpace(afterSpace, beforeSpace, afterSpace);
				
				if(beforeSpace == values[count]){
					possible += " ";
					possible += beforeSpace;
					
					count += 1;
				}
				
				else if(beforeSpace != values[count]){
					match += 1;
					possible += " ";
					possible += beforeSpace;
					
					
				}
				if(match > 1){break;}
				check++;
				
			}

			if(check == leng+1 && match < 2 && findlength(fixed) == leng+1 && possible != word) {cout << " " << w;}
		}
		else{
			match += 1;
			possible += beforeSpace;
			

			int leng = findlength(word);


			while(check < leng+1){
				
				splitOnSpace(afterSpace, beforeSpace, afterSpace);
				
				if(beforeSpace == values[count]){
					possible += " ";
					possible += beforeSpace;
					
					count += 1;
				}
				
				else if(beforeSpace != values[count]){
					match += 1;
					possible += " ";
					possible += beforeSpace;
					
					
				}
				if(match > 1){break;}
				check++;
				
			} //slightly modified replace code to allow for an extra phenome
			if(check == leng+1 && match < 2 && findlength(fixed) == leng+1 && possible != word) {cout << " " << w;}
		}			
	}}
	cout << endl;
}
	

void repp(string word){


	ifstream gin2("cmudict.0.7a");
	if (gin2.fail()) 
	{
   	 cerr << "File cannot be opened for reading." << endl;
   	 exit(1); // exit if failed to open the file
	}
	
	string junk, pro, w, possible;     // new string variable
	getline(gin2, junk); // read one line from the file 

	int match = 0;
	
	string a;
	splitOnSpace(word, beforeSpace, afterSpace);
	a = beforeSpace;

	string values[9];

	values[0] = {beforeSpace};

	for(int i = 1; i < 9; i++){
		splitOnSpace(afterSpace, beforeSpace, afterSpace);
		values[i] = {beforeSpace};
	}

	cout << "Replace phoneme  :";
	while(gin2 >> w) { 
		getline(gin2, pro);
		string fixed = removeLeadingSpaces(pro);
		if(clean(w)==true){
		splitOnSpace(fixed, beforeSpace, afterSpace);

		possible = "";
		int check = 1;
		match = 0;
		int count = 0;

		if(beforeSpace == a){

			possible += beforeSpace;
			
			count += 1;
			int leng = findlength(word);


			while(check < leng){
				
				splitOnSpace(afterSpace, beforeSpace, afterSpace);
				
				if(beforeSpace == values[check]){
					possible += " ";
					possible += beforeSpace;
					
					count += 1;
				}
				
				else if(beforeSpace != values[check]){
					match += 1;
					possible += " ";
					possible += beforeSpace;
					
					count += 1;
				}
				if(match > 1){break;}
				check++;
				
			}
			if(check == leng && match < 2 && findlength(fixed) == leng && possible != word) {cout << " " << w;}
		}
		else{
			match += 1;
			possible += beforeSpace;
			
			count += 1;
			int leng = findlength(word);


			while(check < leng){
				
				splitOnSpace(afterSpace, beforeSpace, afterSpace);
				
				if(beforeSpace == values[check]){
					possible += " ";
					possible += beforeSpace;
					
					count += 1;
				}
				
				else if(beforeSpace != values[check]){
					match += 1;
					possible += " ";
					possible += beforeSpace;
					
					count += 1;
				}
				if(match > 1){break;}
				check++;
				
			}
			if(check == leng && match < 2 && findlength(fixed) == leng && possible != word) {cout << " " << w;}	
		}			
	}}
	cout << endl;
}
	
string values[9];

int main()
{
	//std::cout << std::filesystem::current_path().string() << std::endl;

	ifstream fin("cmudict.0.7a");
	if (fin.fail()) 
	{
   	 cerr << "File cannot be opened for reading." << endl;
   	 exit(1); // exit if failed to open the file
	}

	string junk;        // new string variable
	getline(fin, junk); // read one line from the file 

	string pro, input, newpro = "filler";

	cin >> input;
	
	string word = "";

	for(int i = 0; i <input.size(); i++){
		char x = toupper(input[i]);
		word += x;
	}

	while(fin >> pro) 
	{ 
		
		if(word == pro){
			
			getline(fin, pro);
			splitOnSpace(pro, beforeSpace, afterSpace);
			newpro = afterSpace;
			cout << "Pronunciation    :" << afterSpace << endl << endl;	
			
		}
		
		splitOnSpace(pro, beforeSpace, afterSpace);
		
		if(newpro == afterSpace){
 			findident(word, newpro);
		}	
	}
	if(newpro == "filler"){
		cout << "Not Found";
		return -1;
	}



	newpro = removeLeadingSpaces(newpro);
	addp(newpro);
   	removep(newpro);
	repp(newpro);

	
return 0;

}
