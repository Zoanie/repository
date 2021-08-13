//============================================================================
// Name        : hackerrank-attribute-parser.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.hackerrank.com/challenges/attribute-parser/problem
//============================================================================


#include <bits/stdc++.h>

using namespace std;

/*
 * Attribute Parser
 *
 * Note: The discussion section on hackerrank.com has many complaints about the problem being
 * too difficult for the rating.  The discussion notes that the problem is not well formed
 * in that it allows erroneous input arguments without being checked.
 *
This challenge works with a custom-designed markup language HRML. In HRML, each element consists
of a starting and ending tag, and there are attributes associated with each tag. Only starting
tags can have attributes. We can call an attribute by referencing the tag, followed by a tilde,
'~' and the name of the attribute. The tags may also be nested.

The opening tags follow the format:

<tag-name attribute1-name = "value1" attribute2-name = "value2" ...>

The closing tags follow the format:

</tag-name>

The attributes are referenced as:

tag1~value
tag1.tag2~name
Given the source code in HRML format consisting of  lines, answer  queries. For each query, print
the value of the attribute specified. Print "Not Found!" if the attribute does not exist.

Example

HRML listing
<tag1 value = "value">
<tag2 name = "name">
<tag3 another="another" final="final">
</tag3>
</tag2>
</tag1>

Queries
tag1~value
tag1.tag2.tag3~name
tag1.tag2~value
Here, tag2 is nested within tag1, so attributes of tag2 are accessed as tag1.tag2~<attribute>. Results of the queries are:

Query                 Value
tag1~value            "value"
tag1.tag2.tag3~name   "Not Found!"
tag1.tag2.tag3~final  "final"
Input Format

The first line consists of two space separated integers,  and .  specifies the number of lines
in the HRML source program.  specifies the number of queries.

The following  lines consist of either an opening tag with zero or more attributes or a closing
tag. There is a space after the tag-name, attribute-name, '=' and value.There is no space after
the last value. If there are no attributes there is no space after tag name.

 queries follow. Each query consists of string that references an attribute in the source program.
 More formally, each query is of the form ~ where  and  are valid tags in the input.

Constraints

Each line in the source program contains, at most,  characters.
Every reference to the attributes in the  queries contains at most  characters.
All tag names are unique and the HRML source program is logically correct, i.e. valid nesting.
A tag can may have no attributes.
Output Format

Print the value of the attribute for each query. Print "Not Found!" without quotes if the
attribute does not exist.

Sample Input 1:
4 4
<tag1 value = "HelloWorld">
<tag2 name = "Name1">
</tag2>
</tag1>
tag1.tag2~name
tag1~name
tag1~value
tag2~name

Sample Output 1:
Name1
Not Found!
HelloWorld

Sample Input 2:
6 4
<tag1 value = "valueA">
<tag2 name = "nameB">
<tag3 another = "anotherC" final="finalD">
</tag3>
</tag2>
</tag1>
tag1~value
tag1.tag2~name
tag1.tag2.tag3~final
tag1.tag2.tag3~another

Sample Output 2:
tag1~value            "value"
tag1.tag2.tag3~name   "Not Found!"
tag1.tag2.tag3~final  "final"

 */

// https://stackoverflow.com/a/1493195/6101104
template < class ContainerT >
void tokenize(const string& str, ContainerT& tokens,
              const string& delimiters = " ", bool trimEmpty = false)
{
   size_t pos, lastPos = 0, length = str.length();

   using value_type = typename ContainerT::value_type;
   using size_type  = typename ContainerT::size_type;

   while(lastPos < length + 1)
   {
      pos = str.find_first_of(delimiters, lastPos);
      if(pos == std::string::npos)
      {
         pos = length;
      }

      if(pos != lastPos || !trimEmpty)
         tokens.push_back(value_type(str.data()+lastPos,
               (size_type)pos-lastPos ));

      lastPos = pos + 1;
   }
}


int buildTagMap(int num_lines, unordered_map <string, string>&tagMap, istream& str) {

    enum TokenType { TOK_QUERY, TOK_KEY, TOK_VALUE };

    //int line_num=0;
    vector<string> tagKeys;
    vector<string> tagList;
    string line;

    while(num_lines) {
    	vector<string> tokens;
		getline(str, line);
		//printf("Remaining lines = %d, line = %s\n", num_lines, line.c_str());
		//int num_tokens=0;
		if(line.find("</") == 0) {
			tagList.pop_back();
		}
		else {
			tokenize(line, tokens, "<> =\"", true);
		}

		for(size_t i=0, token_type=TOK_QUERY; i<tokens.size(); i++) {
			string& tok = tokens[i];
			string tag;
			//printf("line %d token %d = '%s'\n", line_num++, num_tokens++, tok.c_str());

			// "This function shall NOT be called on empty strings."
			if (tagList.size() > 0)
				tag = tagList.back();
			else
				tag = "";

			if(token_type == TOK_QUERY) {
				if (tagList.size() > 0)
					tagList.push_back(tag + "." + tok);
				else
					tagList.push_back(tok);
				token_type = TOK_KEY;
			}
			else if (token_type == TOK_KEY) {
				tagKeys.push_back(tag + "~" + tok);
				token_type = TOK_VALUE;
			}
			else if (token_type == TOK_VALUE) {
				//printf("map: key=%s, val=%s\n", tagKeys.back().c_str(), tok.c_str());
				tagMap.emplace(make_pair(tagKeys.back(), tok));
				token_type = TOK_KEY;
			}
		}
		num_lines--;
    }

    return num_lines;
}


int main() {
	cout << "https://www.hackerrank.com/challenges/attribute-parser/problem\n" << endl;
	{
	    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
	    int num;
	    cin >> num;
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    int numbers[num];
	    // We can use either way, using ss or cin below...
	    //string line;
	    //getline(cin,line);
	    //stringstream ss(line);

	    for(int i=0; i<num; i++) {
	        cin >> numbers[i];
	    }
	    for(int i=num-1; i>=0; i--) {
	        cout << numbers[i];
	        if(i>0) cout << " ";
	    }
	    cout << endl;
	    return 0;
	}
    int num_lines=0;
    int num_queries=0;
    bool fileio = true;
    string line;
	string fname("hrml3.txt");
	ifstream ifile(fname);
	istream& str = fileio ? ifile : cin;

    getline(str,line);
    stringstream ss(line);
    ss >> num_lines;
    ss >> num_queries;

	if(fileio) {
	    if(ifile.fail()) {
	    	cout << "Unable to open file " << fname << endl;
	    	return -1;
	    }
	}

	// direct cin I/O can screw up the arguments very easily
    if(num_lines < 1 || num_lines > 20) {
    	cout << "Invalid number of input lines = " << num_lines << endl;
    	return -1;
    }
    if(num_queries < 1 || num_queries > 20) {
    	cout << "Invalid number of input lines = " << num_queries << endl;
    	return -1;
    }

	unordered_map <string, string> tagQueryMap;
    buildTagMap(num_lines, tagQueryMap, str);

    while(num_queries--) {
        getline(str,line);
    	//cout << "Query: " << line << endl;
        string value = tagQueryMap[line];
        if(value=="") { value = "Not Found!";}
        cout << value << endl;
    }

	return 0;
}
