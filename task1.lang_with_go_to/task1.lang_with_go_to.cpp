#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Pair {
    string strng;
    int count;
};


int main()
{
    int SIZE = 0;
    int sizeOfPairsMas = 25;
    int alreadyOnMas = 0;
    Pair* pairsMas = new Pair[sizeOfPairsMas];
    string str;

    string stopWords[] =
    { "a", "an", "am", "and", "are", "at", "but", "by",
      "for", "from", "in", "into", "is", "not", "of",
      "off", "on", "onto", "or", "the", "to", "towith", "within"
    };

    char punctionMarks[] = { '!', '?', ',','.', ':', ';' };

    ifstream file("text.txt");
inputWhile:
    if (file >> str) {
        int i = 0;
        int j = 0;
        int k = 0;
        int o = 0;
        int p = 0;
        int sizeOfString = 0;
        cout << str << endl;
    strSize:
        if (str[sizeOfString]) {
            sizeOfString++;
            goto strSize;
        }

        //converting to lower case
    toLowerCycle:
        if (k < sizeOfString) {
            if (str[k] <= 'Z' && str[k] >= 'A') {
                str[k] += 'a' - 'A';
            }
            k++;
            goto toLowerCycle;
        }
        //filter the punctuation marks
    puncMarkCycle:
        if (p < 6) {
            if (str[sizeOfString - 1] == punctionMarks[p]) {
                int t = 0;
                sizeOfString--;
                string tmpStr = "";
            copyStrCycle:
                if (t < sizeOfString) {
                    tmpStr += str[t];
                    t++;
                    goto copyStrCycle;
                }
                str = tmpStr;
                goto cycleStopWords;
            }
            p++;
            goto puncMarkCycle;
        }

        //filtering the stop words
    cycleStopWords:
        if (j < 23) {
            if (str == stopWords[j]) {
                goto inputWhile;
            }
            j++;
            goto cycleStopWords;
        }

        // checking if the word is already on mas
        // and adding if it's not
    cycleAlreadyOnMas:
        if (i < alreadyOnMas) {
            if (pairsMas[i].strng == str) {
                pairsMas[i].count++;
                goto inputWhile;
            }
            i++;
            goto cycleAlreadyOnMas;
        }
        else {
            pairsMas[alreadyOnMas] = { str, 1 };
            alreadyOnMas++;
        }

        //incerase the array size of needed
        if (alreadyOnMas + 1 == sizeOfPairsMas) {
            sizeOfPairsMas *= 2;
            Pair* tmpPairsMas = new Pair[sizeOfPairsMas];
            int i = 0;
        copyingWords:
            if (i >= alreadyOnMas) {
                goto allHasBeenCopied;
            }
            tmpPairsMas[i] = pairsMas[i];
            i++;
            goto copyingWords;
        allHasBeenCopied:
            delete[] pairsMas;
            pairsMas = tmpPairsMas;
        }
        goto inputWhile;
    }
    else {
        //bubbleSort
        int i = 0;
    bubbleSortCycleI:
        if (i < alreadyOnMas - 1) {
            int j = 0;
        bubbleSortCycleJ:
            if (j < alreadyOnMas - i - 1) {
                if (pairsMas[j].count < pairsMas[j + 1].count) {
                    Pair tmp;
                    tmp = pairsMas[j + 1];
                    pairsMas[j + 1] = pairsMas[j];
                    pairsMas[j] = tmp;
                }
                j++;
                goto bubbleSortCycleJ;
            }
            i++;
            goto bubbleSortCycleI;
        }

        //output the result
        int toOutput = 0;
        if (alreadyOnMas > 25) {
            toOutput = 25;
        }
        else {
            toOutput = alreadyOnMas;
        }
        int k = 0;
    outputCycle:
        if (k < toOutput) {
            cout << pairsMas[k].strng;
            cout << " - ";
            cout << pairsMas[k].count << endl;
            k++;
            goto outputCycle;
        }
    }
}
