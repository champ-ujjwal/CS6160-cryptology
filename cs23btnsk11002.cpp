// UJJWAL KUMAR
// CS23BTNSK11002
#include <bits/stdc++.h>
using namespace std;

string xorStrings(const string &a, const string &b)
{
    string result;
    for (size_t i = 0; i < a.length(); ++i)
    {
        result += char(a[i] ^ b[i]);
    }
    return result;
}

vector<int> xorIntVectors(const vector<int> &a, const vector<int> &b)
{
    vector<int> result;
    for (size_t i = 0; i < a.size(); ++i)
    {
        result.push_back(a[i] ^ b[i]);
    }
    return result;
}

bool isUpper(char x)
{
    return (x >= 'A' && x <= 'Z');
}

bool isLower(char x)
{
    return (x >= 'a' && x <= 'z');
}

string listToCharString(const vector<int> &lis)
{
    string setOfPlainText = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,?!-:\";' ";
    string res = "";
    for (size_t i = 0; i < lis.size(); ++i)
    {
        char ch = char(lis[i]);
        if (setOfPlainText.find(ch) != string::npos)
        {
            res += ch;
        }
        else
        {
            res += '_';
        }
    }
    return res;
}

int main()
{
    ifstream f("streamciphertexts.txt");

    vector<string> ciphers;
    string cipher;

    while (getline(f, cipher))
    {
        ciphers.push_back(cipher);
    }

    vector<vector<int>> ciphersInt;
    for (const string &cipher : ciphers)
    {
        vector<int> lis2;
        for (size_t i = 0; i < cipher.length(); i += 2)
        {
            lis2.push_back(stoi(cipher.substr(i, 2), 0, 16));
        }
        ciphersInt.push_back(lis2);
    }

    vector<int> key(150, 0);

    for (size_t i = 0; i < ciphersInt.size(); ++i)
    {
        vector<int> spaceIndex;
        for (size_t j = i + 1; j < ciphersInt.size(); ++j)
        {
            vector<int> xorred = xorIntVectors(ciphersInt[i], ciphersInt[j]);
            for (size_t k = 0; k < xorred.size(); ++k)
            {
                if (isUpper(char(xorred[k])) || isLower(char(xorred[k])))
                {
                    if (k < spaceIndex.size())
                    {
                        spaceIndex[k] += 1;
                    }
                    else
                    {
                        spaceIndex.push_back(1);
                    }
                }
            }
        }

        for (size_t k = 0; k < spaceIndex.size(); ++k)
        {
            if (spaceIndex[k] > 2)
            {
                key[k] = ciphersInt[i][k] ^ ' ';
            }
        }
    }



    vector<string> messages;
    cout << "Expected message be like :" << endl;

    for (size_t i = 0; i < ciphersInt.size(); ++i)
    {
        vector<int> cipher = ciphersInt[i];
        vector<int> broken = xorIntVectors(cipher, key);
        string message = listToCharString(broken);
        if (i < messages.size())
        {
            messages[i] = message;
        }
        else
        {
            messages.push_back(message);
        }
        cout << i << " " << message << endl;
    }

    cout << endl
         << endl
         << "\n\nFilling  the blanks:" << endl;

    // filling the blank indices by using common sense and looking pattern of corrosponding indices pt
    //  by filling indices also updating the value of key
    int index;
    char Letter;
    // int i=0;
    // char str[] = {'E', 'n', 'p', 'd', 'c', 'b', 'c', 'o', 'h', 'e', 'i', 'c'};
    string str1 = "Enpdcbcoheic";
    int arr[] = {0, 1, 14, 16, 26, 42, 46, 33, 37, 38, 29, 30};
    for (int i = 0; i < 12; i++)
    {
        if (i < 7)
        {
            index = 0;
        }
        else if (i < 10)
        {
            index = 2;
        }
        else
        {
            index = 3;
        }
        key[arr[i]] = str1[i] ^ ciphersInt[index][arr[i]];
    }

    key[40] = 'e' ^ ciphersInt[11][40];
    key[42] = 'r' ^ ciphersInt[2][42];
    key[14] = 'y' ^ ciphersInt[2][14];
    key[16] = 'i' ^ ciphersInt[3][16];
    key[33] = 'y' ^ ciphersInt[6][33];
    key[53] = 's' ^ ciphersInt[7][53];
    key[54] = 't' ^ ciphersInt[10][54];
    key[55] = 'i' ^ ciphersInt[10][55];
    key[56] = 'o' ^ ciphersInt[10][56];
    key[57] = 'n' ^ ciphersInt[10][57];
    key[58] = 'i' ^ ciphersInt[0][58];
    key[59] = 'c' ^ ciphersInt[0][59];
    key[61] = 't' ^ ciphersInt[0][61];
    key[62] = 'e' ^ ciphersInt[0][62];
    key[63] = 'd' ^ ciphersInt[0][63];
    key[60] = 'n' ^ ciphersInt[9][60];
    key[64] = 'o' ^ ciphersInt[6][64];
    key[65] = 'w' ^ ciphersInt[6][65];
    key[66] = 'e' ^ ciphersInt[11][66];
    key[70] = 'u' ^ ciphersInt[11][70];
    key[71] = 't' ^ ciphersInt[0][71];
    key[73] = 'o' ^ ciphersInt[0][73];
    key[74] = 'n' ^ ciphersInt[0][74];
    key[75] = 'n' ^ ciphersInt[1][75];
    key[78] = 'l' ^ ciphersInt[6][78];
    key[84] = 'i' ^ ciphersInt[11][84];
    key[85] = 't' ^ ciphersInt[11][85];
    key[89] = 'f' ^ ciphersInt[1][89];
    key[90] = 'e' ^ ciphersInt[1][90];
    key[91] = 'e' ^ ciphersInt[1][91];
    key[81] = 'u' ^ ciphersInt[2][81];
    key[82] = 'p' ^ ciphersInt[2][82];
    key[94] = 'i' ^ ciphersInt[5][94];
    key[95] = 'c' ^ ciphersInt[5][95];
    key[96] = 's' ^ ciphersInt[9][96];
    key[99] = 'r' ^ ciphersInt[11][99];
    key[100] = 'm' ^ ciphersInt[1][100];
    key[102] = 'b' ^ ciphersInt[2][102];
    key[103] = 'e' ^ ciphersInt[2][103];
    key[104] = 'l' ^ ciphersInt[2][104];
    key[105] = 'i' ^ ciphersInt[2][105];
    key[106] = 'e' ^ ciphersInt[2][106];
    key[107] = 'v' ^ ciphersInt[2][107];
    key[108] = 'e' ^ ciphersInt[2][108];
    key[110] = 'b' ^ ciphersInt[10][110];
    key[111] = 'e' ^ ciphersInt[10][111];
    key[113] = 'b' ^ ciphersInt[2][113];
    key[114] = 'e' ^ ciphersInt[2][114];
    key[116] = 'j' ^ ciphersInt[2][116];
    key[117] = 'u' ^ ciphersInt[2][117];
    key[118] = 's' ^ ciphersInt[2][118];
    key[119] = 'e' ^ ciphersInt[11][119];
    key[120] = 'n' ^ ciphersInt[11][120];
    key[121] = 't' ^ ciphersInt[11][121];
    key[122] = 'A' ^ ciphersInt[2][122];
    key[123] = 'b' ^ ciphersInt[2][123];
    key[124] = 'r' ^ ciphersInt[2][124];
    key[125] = 'a' ^ ciphersInt[2][125];
    key[126] = 'h' ^ ciphersInt[2][126];
    key[127] = 'a' ^ ciphersInt[2][127];
    key[128] = 'm' ^ ciphersInt[2][128];
    key[129] = ' ' ^ ciphersInt[2][129];
    key[130] = 'L' ^ ciphersInt[2][130];
    key[131] = 'i' ^ ciphersInt[2][131];
    key[132] = 'n' ^ ciphersInt[2][132];
    key[133] = 'c' ^ ciphersInt[2][133];
    key[134] = 'o' ^ ciphersInt[2][134];
    key[135] = 'l' ^ ciphersInt[2][135];
    key[136] = 'n' ^ ciphersInt[2][136];
    key[137] = 's' ^ ciphersInt[11][137];
    key[138] = 'e' ^ ciphersInt[11][138];
    key[139] = 'r' ^ ciphersInt[11][139];
    // int key_indices[] = {40, 42, 14, 16, 33, 53, 54, 55, 56, 57, 58, 59, 61, 62, 63, 60, 64, 65, 66, 70, 71, 73, 74, 75, 78, 84, 85, 89, 90, 91, 81, 82, 94, 95, 96, 99, 100, 102, 103, 104, 105, 106, 107, 108, 110, 111, 113, 114, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139};
    // int first_indices_ciphersInt[] = {11, 2, 2, 3, 6, 7, 10, 10, 10, 10, 0, 0, 0, 0, 0, 9, 6, 6, 11, 11, 0, 0, 0, 1, 6, 11, 11, 1, 1, 1, 2, 2, 5, 5, 9, 11, 1, 2, 2, 2, 2, 2, 2, 2, 2, 10, 10, 2, 2, 2, 2, 2, 11, 11, 11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11, 11, 11};
    // // string str="eryiystionictednoweutonnlitfeepicsrmbelievebejusentAbraham Lincolnser";
    // int n=sizeof(key_indices)/sizeof(int);
    // char string_characters[] = {'e', 'r', 'y', 'i', 'y', 's', 't', 'i', 'o', 'n', 'i', 'c', 't', 'e', 'd', 'n', 'o', 'w', 'e', 'u', 't', 'o', 'n', 'n', 'l', 'i', 't', 'f', 'e', 'e', 'u', 'p', 'i', 'c', 's', 'r', 'm', 'b', 'e', 'l', 'i', 'e', 'v', 'e', 'b', 'e', 'b', 'e', 'j', 'u', 's', 'e', 'n', 't', 'A', 'b', 'r', 'a', 'h', 'a', 'm', ' ', 'L', 'i', 'n', 'c', 'o', 'l', 'n', 's', 'e', 'r'};
    // for(int i=0;i<n;i++){
    //     key[key_indices[i]] = first_indices_ciphersInt[i] ^ ciphersInt[first_indices_ciphersInt[i]][key_indices[i]];
    // }
    //   string s="Lincoln";
    //   for(int i=0;i<s.length();i++){
    //     key[131+i] = s[i] ^ ciphersInt[2][131+i];
    //   }
    //   key[129] = ' ' ^ ciphersInt[2][128];
    //   key[131] = 'G' ^ ciphersInt[11][131];
    //   key[132] = 'o' ^ ciphersInt[11][132];
    //   key[133] = 'l' ^ ciphersInt[11][133];
    //   key[131] = 'i' ^ ciphersInt[2][131];
    //   key[132] = 'n' ^ ciphersInt[2][132];

    //   key[98] = 'l' ^ ciphersInt[5][98];
    //   key[99] = 'y' ^ ciphersInt[5][99];
    //  key[64] = 'f' ^ ciphersInt[9][64];
    //  key[65] = 'u' ^ ciphersInt[9][65];
    //  key[66] = 'l' ^ ciphersInt[9][66];
    //  key[60] = 'm' ^ ciphersInt[3][60];
    // key[1] = 'n' ^ ciphersInt[index][1];
    // key[14] = 'p' ^ ciphersInt[index][14];
    // key[16] = 'd' ^ ciphersInt[index][16];
    // key[26] = 'c' ^ ciphersInt[index][26];
    // key[42] = 'b' ^ ciphersInt[index][42];
    // key[46] = 'c' ^ ciphersInt[index][46];
    // index=2;
    // key[33] = 'o' ^ ciphersInt[index][33];
    // key[37] = 'h' ^ ciphersInt[index][37];
    // key[38] = 'e' ^ ciphersInt[index][38];
    // index=3;
    // key[29] = 'i' ^ ciphersInt[index][29];
    // key[30] = 'c' ^ ciphersInt[index][30];
    // index=11;
    // key[16] = 'n' ^ ciphersInt[index][16];


    string plainTextFirst, PlainTextLast;
    for (size_t i = 0; i < ciphersInt.size(); ++i)
    {
        vector<int> cipher = ciphersInt[i];
        vector<int> broken = xorIntVectors(cipher, key);
        string message = listToCharString(broken);
        if (i < messages.size())
        {
            messages[i] = message;
        }
        else
        {
            messages.push_back(message);
        }
        cout << i << " " << message << endl;
        if (i == 0)
        {
            plainTextFirst = message;
        }
        if (i == 11)
        {
            PlainTextLast = message;
        }
    }

    cout << "\n\n---------------------------------------------OUTPUT----------------------------------------------------------------------------------------------" << endl;
    cout << "\n\nThe first plain text : " << plainTextFirst << "\n\n";
    cout << "The last plain text : " << PlainTextLast << "\n\n";
    // }
    cout << "\n\nthe key : ";
    for (int i = 0; i < key.size(); i++)
    {
        cout << key[i] << " ";
    }
    cout << "\n\n\n";

    return 0;
}
