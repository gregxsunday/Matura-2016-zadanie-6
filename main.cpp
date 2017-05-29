#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

const char alf[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int round_key(int key, int char_index) //rounding key NOT using modulo allowed me to use negative keys
{
    int result = key + char_index;

    while(result < 0 || result > 25)
    {
        if(result < 0)
            result += 26;
        else
            result -= 26;
    }

    return result;
}

string code(string word_to_code, int key = 107)
{
    string result;

    for(int i = 0; i < word_to_code.size(); i++)
    {
        result += alf[round_key(key, ((int)word_to_code.at(i) - 65))];
    }

    return result;
}

int uncode(string word, string word_coded) //returns key that that the word was coded with. Only first 3 chars are checked.
{
    int result = 0;
    int keys[3];
    for(int i = 0; i < 3; i++)
    {
        keys[i] = round_key(word_coded.at(i), (-1*word.at(i)));
    }

    if(keys[0] == keys[1] || keys[0] == keys[2])
        return keys[0];
    else
        return keys[1];
}

int main()
{
    //6.1
    fstream source_file, output_file;
    string line;
    source_file.open("Dane_PR2\\dane_6_1.txt", ios::in);
    output_file.open("C:\\Users\\Grzegorz\\Documents\\matury\\2016\\wyniki_6_1.txt", ios::out);

    while(getline(source_file, line))
    {
        output_file << code(line) << endl;
    }
    source_file.close();
    output_file.close();

    //6.2
    source_file.open("Dane_PR2\\dane_6_2.txt", ios::in);
    output_file.open("C:\\Users\\Grzegorz\\Documents\\matury\\2016\\wyniki_6_2.txt", ios::out);

    while(getline(source_file, line))
    {
        string word_to_code = line.substr(0, line.find(' '));
        int key = atoi(line.substr(line.find(' ') + 1).c_str());
        output_file << code(word_to_code, -key) << endl;
    }

    source_file.close();
    output_file.close();

    //6.3
    source_file.open("Dane_PR2\\dane_6_3.txt", ios::in);
    output_file.open("C:\\Users\\Grzegorz\\Documents\\matury\\2016\\wyniki_6_3.txt", ios::out);

    while(getline(source_file, line))
    {
        string word = line.substr(0, line.find(' '));
        string coded = line.substr(line.find(' ') + 1);
        int key = uncode(word, coded);
        if(coded != code(word, key))
            output_file << word << endl;
    }
    source_file.close();
    output_file.close();
    return 0;
}
