
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
//standard imports

#include "/Libraries/crypto++/modes.h"
#include "/Libraries/crypto++/aes.h"
#include "/Libraries/crypto++/filters.h"
//include cryptopp library files

using namespace std;
using namespace CryptoPP;
/*
To Do:
	Add GUI with file browser
	Encrypt key with password
	Write output to seprate file
	???
	Profit
*/
int main(int argc, char* argv[])
{
    //16 byte key (128-bit)

    byte key[ AES::DEFAULT_KEYLENGTH ], iv[ AES::BLOCKSIZE ];
    memset( key, 0x00, AES::DEFAULT_KEYLENGTH );t
    memset( iv, 0x00, AES::BLOCKSIZE );
	//Create key

    string inputText;
	string line;
	string readFile;

	cout<<"Path to file to encrypt(includeing extension): ";
	cin>>readFile;
	cout<<endl;

	ifstream file(readFile);
	while (file>>line)
	{
		inputText += line;
		inputText.push_back('/n');
	}
	//Read the file 

    string encryptedText;
    string decryptedtext;
	cout<<"Key:"<<key<<endl<<endl;
    // Dump Input Text

    cout << "Input Text (" << inputText.size() << " bytes)" << endl;
    cout << inputText;
    cout << endl << endl;

    //Encrypt Text
    AES::Encryption aesEncryption(key, AES::DEFAULT_KEYLENGTH);
    CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );

    StreamTransformationFilter stfEncryptor(cbcEncryption, new StringSink( encryptedText ) );
    stfEncryptor.Put( reinterpret_cast<const unsigned char*>( inputText.c_str() ), inputText.length() + 1 );
    stfEncryptor.MessageEnd();

    // Dump Encrypted Text
    cout << "Encrypted Text (" << encryptedText.size() << " bytes)" << endl;

    for( int i = 0; i < encryptedText.size(); i++ ) {

        cout << "0x" << hex << (0xFF & static_cast<byte>(encryptedText[i])) << " ";
    }

    cout << endl << endl;

    // Decrypt
    AES::Decryption aesDecryption(key, AES::DEFAULT_KEYLENGTH);
    CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

    StreamTransformationFilter stfDecryptor(cbcDecryption, new StringSink( decryptedtext ) );
    stfDecryptor.Put( reinterpret_cast<const unsigned char*>( encryptedText.c_str() ), encryptedText.size() );
    stfDecryptor.MessageEnd();

    // Dump Decrypted Text
    cout << "Decrypted Text: " << endl;
    cout << decryptedtext;
    cout << endl << endl;
	
	system("pause");

    return 0;
}