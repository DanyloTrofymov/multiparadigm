//#include <iostream>
//#include <string>
//#include <fstream>
//
//using namespace std;
//
//struct Pair {
//    string strng;
//    int count;
//};
//
//
//int main()
//{
//    int SIZE = 0;
//    int sizeOfPairsMas = 25;
//    int alreadyOnMas = 0;
//    Pair* pairsMas = new Pair[sizeOfPairsMas];
//    string str;
//
//    string stopWords[] =
//    { "a", "an", "am", "and", "are", "at", "but", "by",
//      "for", "from", "in", "into", "is", "not", "of",
//      "off", "on", "onto", "or", "the", "to", "towith", "within"
//    };
//
//    char punctionMarks[] = { '!', '?', ',','.', ':', ';' };
//
//    ifstream file("text.txt");
//inputWhile:
//    if (file >> str) {
//        int i = 0;
//        int j = 0;
//        int sizeOfString = 0;
//
//    strSize:
//        if (str[sizeOfString]) {
//            sizeOfString++;
//            goto strSize;
//        }
//
//        //converting to lower case
//    toLowerCycle:
//        if (i < sizeOfString) {
//            if (str[i] <= 'Z' && str[i] >= 'A') {
//                str[i] += 'a' - 'A';
//            }
//            i++;
//            goto toLowerCycle;
//        }
//        i = 0;
//        //filter the punctuation marks
//    puncMarkCycle:
//        if (i < 6) {
//            if (str[sizeOfString - 1] == punctionMarks[i]) {
//                j = 0;
//                sizeOfString--;
//                string tmpStr = "";
//            copyStrCycle:
//                if (j < sizeOfString) {
//                    tmpStr += str[j];
//                    j++;
//                    goto copyStrCycle;
//                }
//                str = tmpStr;
//                i = 0;
//                j = 0;
//                goto cycleStopWords;
//            }
//            i++;
//            goto puncMarkCycle;
//        }
//        i = 0;
//        j = 0;
//        //filtering the stop words
//    cycleStopWords:
//        if (i < 23) {
//            if (str == stopWords[i]) {
//                goto inputWhile;
//            }
//            i++;
//            goto cycleStopWords;
//        }
//        i = 0;
//        // checking if the word is already on mas
//        // and adding if it's not
//    cycleAlreadyOnMas:
//        if (i < alreadyOnMas) {
//            if (pairsMas[i].strng == str) {
//                pairsMas[i].count++;
//                goto inputWhile;
//            }
//            i++;
//            goto cycleAlreadyOnMas;
//        }
//        else {
//            pairsMas[alreadyOnMas] = { str, 1 };
//            alreadyOnMas++;
//        }
//        i = 0;
//        //incerase the array size of needed
//        if (alreadyOnMas + 1 == sizeOfPairsMas) {
//            sizeOfPairsMas *= 2;
//            Pair* tmpPairsMas = new Pair[sizeOfPairsMas];
//            i = 0;
//        copyingWords:
//            if (i >= alreadyOnMas) {
//                goto allHasBeenCopied;
//            }
//            tmpPairsMas[i] = pairsMas[i];
//            i++;
//            goto copyingWords;
//        allHasBeenCopied:
//            delete[] pairsMas;
//            pairsMas = tmpPairsMas;
//        }
//        goto inputWhile;
//    }
//    else {
//        //bubbleSort
//        int i = 0;
//    bubbleSortCycleI:
//        if (i < alreadyOnMas - 1) {
//            int j = 0;
//        bubbleSortCycleJ:
//            if (j < alreadyOnMas - i - 1) {
//                if (pairsMas[j].count < pairsMas[j + 1].count) {
//                    Pair tmp;
//                    tmp = pairsMas[j + 1];
//                    pairsMas[j + 1] = pairsMas[j];
//                    pairsMas[j] = tmp;
//                }
//                j++;
//                goto bubbleSortCycleJ;
//            }
//            i++;
//            goto bubbleSortCycleI;
//        }
//
//        //output the result
//        int toOutput = 0;
//        if (alreadyOnMas > 25) {
//            toOutput = 25;
//        }
//        else {
//            toOutput = alreadyOnMas;
//        }
//        i = 0;
//    outputCycle:
//        if (i < toOutput) {
//            cout << pairsMas[i].strng;
//            cout << " - ";
//            cout << pairsMas[i].count << endl;
//            i++;
//            goto outputCycle;
//        }
//    }
//}
