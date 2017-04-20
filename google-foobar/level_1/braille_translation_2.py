braille_space = '0'*6
braille_capital = '6'
braille_number = '3456'
braille_lower_case_map = ['1', '12', '14', '145', '15', '124', '1245', '125', '24', '245', '13', '123', '134', '1345', '135', '1234', '12345', '1235', '234', '2345', '136', '1236', '2456', '1346', '13456', '1356']
braille_number_map = ['245', '1', '12', '14', '145', '15', '124', '1245', '125', '24']
braille_char_map = {
	','	: '2',
	';'	:	'23',
	':'	: '25',
	'.'	: '256',
	'?'	: '236',
	'!'	: '235',
	'('	:	'5 126',
	')'	:	'5 345',
	'/'	: '456 34',
	'\\' : '456 16',
	'-' : '36',
}

a_code = ord('a')
z_code = ord('z')
A_code = ord('A')
Z_code = ord('Z')
zero_code = ord('0')
nine_code = ord('9')

def get_braille_codes(c):
	ord_c = ord(c)

	if c == ' ':
		return ['0']

	if c in braille_char_map:
		return braille_char_map[c].split(' ')

	if zero_code <= ord_c <= nine_code:
		return [braille_number, braille_number_map[ord_c - zero_code]]

	if A_code <= ord_c <= Z_code:
		return [braille_capital, braille_lower_case_map[ord_c - A_code]]

	if a_code <= ord_c <= z_code:
		return [braille_lower_case_map[ord_c - a_code]]

	# print 'Error no braille found'
	return []

def answer(plaintext):
	braille_codes = []
	for c in plaintext:
		codes = get_braille_codes(c)
		for code in codes:
			braille_codes.append(code)

	retStr = ''
	# print braille_codes
	for code in braille_codes:
		if code == '0':
			retStr += braille_space
		else:
			for i in range(1, 7):
				target = str(i)
				if target in code:
					retStr += '1'
				else:
					retStr += '0'

	return retStr

case_a = '100100101010100110100010'
case_b = '000001110000111010100000010100111000111000100010'
case_c = '000001011110110010100010000000111110101001010100100100101000000000110000111010101010010111101110000000110100101010101101000000010110101001101100111100100010100110000000101010111001100010111010000000011110110010100010000000111000100000101011101111000000100110101010110110'
print answer('code') == case_a
print answer('Braille') == case_b
print answer('The quick brown fox jumped over the lazy dog') == case_c
