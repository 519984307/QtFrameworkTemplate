#ifndef __AUNTEC_AES_DECODER_H
#define __AUNTEC_AES_DECODER_H
#include "auntec_base_types.h"
#include <string>
using namespace std;

namespace AuntecBased
{
/*!
@brief AES�����㷨
*/
class CAESDecoder
{
public:
	/*!
	@brief ����AES������
	@param keySize ��Կ�Ĵ�С, ȡֵ128, 192, 256
	@param key ��Կ
	*/
	CAESDecoder(int keySize, const uint8_t* key);
public:
	/*!
	@brief ����
	@param data ���ݿ飬Ҫ����16�ֽ�
	@return ���ܺ�����ݿ飬16�ֽ�
	*/
	uint8_t* Decode(const uint8_t data[16]);
public:
	~CAESDecoder(void);
private:
	// The number of rounds in AES Cipher. It is simply initiated to zero. The actual value is recieved in the program.
	int m_Nr;
	// The number of 32 bit words in the key. It is simply initiated to zero. The actual value is recieved in the program.
	int m_Nk;
	// The array that stores the round keys.
	uint8_t m_RoundKey[240];
	// The m_Key input to the AES Program
	uint8_t m_Key[32];
	// m_in - it is the array that holds the plain text to be encrypted.
	// m_out - it is the array that holds the key for encryption.
	uint8_t m_in[16];
	uint8_t m_out[16];
	// m_state - the array that holds the intermediate results during encryption.
	uint8_t m_state[4][4];
private:
	// This function produces Nb(m_Nr+1) round keys. The round keys are used in each round to encrypt the states. 
	void KeyExpansion();
	// This function adds the round key to state.
	// The round key is added to the state by an XOR function.
	void AddRoundKey(int round);
	// The SubBytes Function Substitutes the values m_in the
	// m_state matrix with values m_in an S-box.
	void InvSubBytes();
	// The ShiftRows() function shifts the rows m_in the m_state to the left.
	// Each row is shifted with different offset.
	// Offset = Row number. So the first row is not shifted.
	void InvShiftRows();
	// MixColumns function mixes the columns of the m_state matrix.
	// The method used to multiply may be difficult to understand for the inexperienced.
	// Please use the references to gain more information.
	void InvMixColumns();
	// InvCipher is the main function that decrypts the CipherText.
	void InvCipher();
};

/*!
@brief AES �����㷨��CBCģʽ
*/
class CAESCBCDecoder
{
public:
	/*!
	@brief ����AES������
	@param keySize ��Կ�Ĵ�С, ȡֵ128, 192, 256
	@param key ��Կ
	@param iv CBC ģʽ�ĳ�ʼ������ (16�ֽ�)
	*/
	CAESCBCDecoder(int keySize, const uint8_t* key, const uint8_t* iv);

public:
	// ����
	string AESDecode(const string& data);

private:
	///���¿�ʼ�������³�ʼ��iv
	void Restart();
	/*!
	@brief ����
	@param data ���ݿ飬Ҫ����16�ֽ�
	@return ���ܺ�����ݿ飬16�ֽ�
	*/
	uint8_t* Decode(const uint8_t data[16]);
private:
	CAESDecoder m_Decoder; ///< AES���ܶ���
	uint8_t m_IV[16]; ///< ��ʼ������
	uint8_t m_Xor[16]; ///< ������һ�κͽ��ܺ�������������, ��ʼΪm_IV
};
};
#endif
