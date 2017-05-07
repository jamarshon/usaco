import base64
import itertools
import json

# result should be 
# {
#     "colleague": "esteemed",
#     "rabbits": "safe",
#     "success": "great",
#     "efforts": "incredible",
#     "foo": "win!",
#     "achievement": "unlocked"
# }

def xor(s1,s2):
	s1, s2 = [s1, s2] if len(s1) > len(s2) else [s2, s1]
	return ''.join(chr(ord(a) ^ ord(b)) for a,b in zip(s1, itertools.cycle(s2)))

def pretty_print(msg):
	msg = msg.replace('\'', '\"')
	return json.dumps(json.loads(msg), indent=4, separators=(',', ': '))
	
def decode(encrypted_str, username):
	base64_str = base64.b64decode(encrypted_str)
	msg = xor(base64_str, username)
	return pretty_print(msg)

# print decode(encrypted_str, username)