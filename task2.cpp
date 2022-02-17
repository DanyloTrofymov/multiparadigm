#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Pair {
    string strng;
    int pages[101] = {};
    int countOfPages;
};

int main()
{
    int SIZE = 0;
    int sizeOfParsedStr = 25;
    int sizeOfDictionaryMas = 25;
    int alreadyOnDictionary = 0;
    const int LINES_IN_PAGE = 45;
    int currPage = 1;
    int currLine = 1;
    int sizeOfLine = 0;


    Pair* dictionary = new Pair[sizeOfDictionaryMas];
    string line;

    string stopWords[] =
    { "a", "an", "am", "and", "are", "at", "but", "by",
      "for", "from", "in", "into", "is", "not", "of",
      "off", "on", "onto", "or", "the", "to", "towith", "within", ""
    };

    char punctionMarks[] = { '!', '?', ',', '.', ':', ';'};

    ifstream file("text.txt");

    string* parsedStr = new string[sizeOfParsedStr];

pages:
    if (file.peek() != EOF) {
        int alreadyOnParsrdStr = 0;
        int i = 0;
        int j = 0;
        int currWord = 0;

        if (currLine == LINES_IN_PAGE) {
            currPage++;
            currLine = 1;
        }
        getline(file, line);
        sizeOfLine = 0;
        currLine++;
        if (line == "") {
            goto pages;
        }

        // parse by space symbol
        string temp = "";
        char del = ' '; // delimiter for string

    lineSize:
        if (line[sizeOfLine]) {
            sizeOfLine++;
            goto lineSize;
        }

    parseCycle:
        if (i <= sizeOfLine) {
            // If cur char is not del, then append it to the cur "word", otherwise
              // you have completed the word, print it, and start a new word.
            if (line[i] != del && i != sizeOfLine) {
                temp += line[i];
            }
            else {
                // increase array capacity
                if (alreadyOnParsrdStr + 1 == sizeOfParsedStr) {
                    sizeOfParsedStr *= 2;
                    string* tmpStringMas = new string[sizeOfParsedStr];
                    j = 0;
                copyingWordsOne:
                    if (j >= alreadyOnParsrdStr) {
                        goto allHasBeenCopiedOne;
                    }
                    tmpStringMas[j] = parsedStr[j];
                    j++;
                    goto copyingWordsOne;
                allHasBeenCopiedOne:
                    delete[] parsedStr;
                    parsedStr = tmpStringMas;
                }
                parsedStr[alreadyOnParsrdStr] = temp;
                temp = "";
                alreadyOnParsrdStr++;
            }
            i++;
            goto parseCycle;
        }
        
    forEachStringInMas:
        i = 0;
        j = 0;
        int sizeOfString = 0;
        if (currWord < alreadyOnParsrdStr) {
            string str = parsedStr[currWord];
        strSize:
            if (str[sizeOfString]) {
                sizeOfString++;
                goto strSize;
            }
            if (sizeOfString == 0) {
                currWord++;
                goto forEachStringInMas;
            }
            i = 0;
            //converting to lower case
        toLowerCycle:
            if (i < sizeOfString) {
                if (str[i] <= 'Z' && str[i] >= 'A') {
                    str[i] += 'a' - 'A';
                }
                i++;
                goto toLowerCycle;
            }
            i = 0;
            //filter the punctuation marks
        puncMarkCycle:
            if (i < 6) {
                if (str[sizeOfString - 1] == punctionMarks[i]) {
                    j = 0;
                    sizeOfString--;
                    string tmpStr = "";
                copyStrCycle:
                    if (j < sizeOfString) {
                        tmpStr += str[j];
                        j++;
                        goto copyStrCycle;
                    }
                    str = tmpStr;
                    i = 0;
                    j = 0;
                    goto cycleStopWords;
                }
                i++;
                goto puncMarkCycle;
            }
            i = 0;
            j = 0;
            //filtering the stop words
        cycleStopWords:
            if (i < 24) {
                if (str == stopWords[i]) {
                    currWord++;
                    goto forEachStringInMas;
                }
                i++;
                goto cycleStopWords;
            }
            i = 0;
            // checking if the word is already on mas
            // and adding if it's not
            //for (int o = 0; o < alreadyOnDictionary; o++) {
            //    cout << dictionary[o].strng << " ";
            //}
            //cout << endl;

        cycleAlreadyOnMas:
            if (i < alreadyOnDictionary) {
                if (dictionary[i].strng == str) {
                    if (dictionary[i].countOfPages != 101) {
                        dictionary[i].pages[dictionary[i].countOfPages] = currPage;
                        dictionary[i].countOfPages++;
                    }
                    currWord++;
                    goto forEachStringInMas;
                }
                i++;
                goto cycleAlreadyOnMas;
            }
            else {
                dictionary[alreadyOnDictionary].strng = str;
                dictionary[alreadyOnDictionary].pages[0] = currPage;
                dictionary[alreadyOnDictionary].countOfPages = 1;
                alreadyOnDictionary++;

                if (alreadyOnDictionary + 1 == sizeOfDictionaryMas) {
                    sizeOfDictionaryMas *= 2;
                    Pair* tmpDictMas = new Pair[sizeOfDictionaryMas];
                    int n = 0;
                copyingWordsTwo:
                    if (n >= alreadyOnDictionary) {
                        goto allHasBeenCopiedTwo;
                    }
                    tmpDictMas[n] = dictionary[n];
                    n++;
                    goto copyingWordsTwo;
                allHasBeenCopiedTwo:
                    delete[] dictionary;
                    dictionary = tmpDictMas;
                }

                currWord++;
                goto forEachStringInMas;
            }
        }
        goto pages;
    }
    else {

        //bubbleSort
        int i = 0;
        int j = 0;
    bubbleSortCycleI:
        if (i < alreadyOnDictionary - 1) {
            j = 0;
        bubbleSortCycleJ:
            if (j < alreadyOnDictionary - i - 1) {
                if (dictionary[j].strng > dictionary[j + 1].strng) {
                    Pair tmp;
                    tmp = dictionary[j + 1];
                    dictionary[j + 1] = dictionary[j];
                    dictionary[j] = tmp;
                }
                j++;
                goto bubbleSortCycleJ;
            }
            i++;
            goto bubbleSortCycleI;
        }

        // output
        i = 0;
        
    outputCycle:
        j = 0;
        int prevPage = 0;
        if (i < alreadyOnDictionary) {
            if (dictionary[i].countOfPages != 101) {
                cout << dictionary[i].strng;
                cout << " - ";

            numOfPagesCycle:
                if (j < dictionary[i].countOfPages) {
                    if (prevPage != dictionary[i].pages[j]) {
                        prevPage = dictionary[i].pages[j];
                        cout << dictionary[i].pages[j];
                        cout << ", ";
                    }
                    j++;
                    goto numOfPagesCycle;
                }
                cout << endl;
            }
            i++;
            goto outputCycle;
        }
    }
}