/*
Anggota Kelompok
- Muhammad Luthfi Taufiqurrahman (140810190036)
- Gregorius Evangelist Wijayanto (140810190040)
- Ihsanuddin Dwi Prasetyo (140810190048)
Kelas       : B
Deskripsi   : Program Hill Cipher
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int mod26(int num) {
  while (num < 0) {
    num += 26;
  }

  return num % 26;
}

vector<vector<int>> mod26(vector<vector<int>> vec) {
  vector<vector<int>> result;
  for (int i = 0; i < vec.size(); i++) {
    vector<int> temp;
    for (int j = 0; j < vec[i].size(); j++) {
      temp.push_back(mod26(vec[i][j]));
    }

    result.push_back(temp);
  }

  return result;
}

int modInverse(int num) {
  for (int x = 1; x < 26; x++) {
    if (mod26(x * num) == 1) {
      return x;
    }
  }

  return 0;
}

int determinan(vector<vector<int>> vec, int m) {
  if (m == 2) {
    return vec[1][1] * vec[0][0] - vec[0][1] * vec[1][0];
  } else if (m == 3){
    return vec[0][0] * vec[1][1] * vec[2][2]
    +vec[0][1] * vec[1][2] * vec[2][0]
    +vec[0][2] * vec[1][0] * vec[2][1]
    -vec[0][2] * vec[1][1] * vec[2][0]
    -vec[0][0] * vec[1][2] * vec[2][1]
    -vec[0][1] * vec[1][0] * vec[2][2];
  }

  return 0;
}

vector<vector<int>> adjoin(vector<vector<int>> vec, int m) {
  if (m == 2) {
    vector<vector<int>> temp {
      {vec[1][1], -vec[0][1]},
      {-vec[1][0], vec[0][0]},
    };

    return temp;
  } else if (m == 3) {
    vector<vector<int>> kofaktor1 {
      {vec[1][1], vec[1][2]},
      {vec[2][1], vec[2][2]},
    };

    vector<vector<int>> kofaktor2 {
      {vec[1][0], vec[1][2]},
      {vec[2][0], vec[2][2]},
    };

    vector<vector<int>> kofaktor3 {
      {vec[1][0], vec[1][1]},
      {vec[2][0], vec[2][1]},
    };

    vector<vector<int>> kofaktor4 {
      {vec[0][1], vec[0][2]},
      {vec[2][1], vec[2][2]},
    };

    vector<vector<int>> kofaktor5 {
      {vec[0][0], vec[0][2]},
      {vec[2][0], vec[2][2]},
    };

    vector<vector<int>> kofaktor6 {
      {vec[0][0], vec[0][1]},
      {vec[2][0], vec[2][1]},
    };

    vector<vector<int>> kofaktor7 {
      {vec[0][1], vec[0][2]},
      {vec[1][1], vec[1][2]},
    };

    vector<vector<int>> kofaktor8 {
      {vec[0][0], vec[0][2]},
      {vec[1][0], vec[1][2]},
    };

    vector<vector<int>> kofaktor9 {
      {vec[0][0], vec[0][1]},
      {vec[1][0], vec[1][1]},
    };

    vector<vector<int>> temp {
      {determinan(kofaktor1, 2), -1 * determinan(kofaktor4, 2), determinan(kofaktor7, 2)},
      {-1 * determinan(kofaktor2, 2), determinan(kofaktor5, 2), -1 * determinan(kofaktor8, 2)},
      {determinan(kofaktor3, 2), -1 * determinan(kofaktor6, 2), determinan(kofaktor9, 2)},
    };

    return temp;
  }
}

vector<vector<int>> matrixMultiplication(vector<vector<int>> a, vector<vector<int>> b) {
  int jumlah = 0;
  vector<vector<int>> result;
  for(int i = 0; i < a.size(); i++){
    vector<int> temp;
    for(int j = 0; j < b[0].size(); j++){
      for(int k = 0; k < b.size(); k++){
        jumlah = jumlah + a[i][k] * b[k][j];
      }

      temp.push_back(jumlah);
      jumlah = 0;
    }
    result.push_back(temp);
  }

  return result;
}

vector<vector<int>> matrixMultiplication(vector<vector<int>> vec, int num) {
  vector<vector<int>> result;
  for (int i = 0; i < vec.size(); i++) {
    vector<int> temp;
    for (int j = 0; j < vec[i].size(); j++) {
      temp.push_back(vec[i][j] * num);
    }

    result.push_back(temp);
  }

  return result;
}

void printVector2D(vector<vector<int>> vec) {
  for (int i = 0; i < vec.size(); i++) {
    for (int j = 0; j < vec[i].size(); j++) {
      cout << vec[i][j] << "\t";
    }

    cout << '\n';
  }
}

void searchKey(string plain, string cipher, int m) {
  if (m == 2 || m == 3) {
    vector<vector<int>> C, P;

    // Melakukan konversi string plain dan cipher 
    // menjadi array yang berupa angka
    for (int i = 0; i < m; i++) {
      vector<int> pTemp;
      vector<int> cTemp;
      for (int j = 0; j < m; j++) {
        pTemp.push_back((int)(plain[j * m + i] - 'a'));
        cTemp.push_back((int)(cipher[j * m + i] - 'a'));
      }
      C.push_back(cTemp);
      P.push_back(pTemp);
    }

    // mencari inverse dari matriks plainteks
    int deter = determinan(P, m);
    int mod = modInverse(deter);

    // program hanya berjalan jika matriks plainteks memiliki modulus inverse
    if (mod != 0) {
      vector<vector<int>> pInverse = mod26(matrixMultiplication(adjoin(P, m), mod));
      vector<vector<int>> K = mod26(matrixMultiplication(C, pInverse));

      cout << '\n' << "Key Matriks" << "\n";
      printVector2D(K);
    } else {
      cout << "Matriks plainteks tidak mempunyai modular inverse." << '\n';
    }
  } else {
    cout << "Nilai m harus bernilai 2 atau 3." << '\n';
  }
}

int main(int argc, char *argv[]) {
  int input, m;
  string plain, cipher;
  vector<vector<int>> key;
  cout << "###################################" << '\n';
  cout << "#           Hill Cipher           #" << '\n';
  cout << "#          m = 2 or m = 3         #" << '\n';
  cout << "###################################" << '\n';
  cout << "1. Enkripsi" << '\n';
  cout << "2. Dekripsi" << '\n';
  cout << "3. Mencari key" << '\n';
  cout << "Masukkan apapun untuk keluar dari program!" << '\n';
  cout << ">> Pilih: "; cin >> input;
  system("cls");
  switch(input) {
    case 1:
      break;

    case 2:
      break;

    case 3:
      cout << "Masukkan m (2 atau 3) : "; cin >> m;
      if (m == 2 || m == 3) {
        cout << "Plainteks : "; cin >> plain;
        cout << "Cipherteks : "; cin >> cipher;
        if (plain.length() == cipher.length()) {
          searchKey(plain, cipher, m);
        } else {
          cout << "Panjang plainteks dan cipherteks tidak sama!" << '\n';
        }
      } else {
        cout << "Nilai m tidak valid!" << '\n';
      }

      break;
  }

  return 0;
}