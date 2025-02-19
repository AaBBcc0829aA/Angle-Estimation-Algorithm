import ecdsa
import hashlib
import base58

def get_public_key(private_key):
    # Create the private key object
    sk = ecdsa.SigningKey.from_secret_exponent(private_key, curve=ecdsa.SECP256k1)
    # Get the public key in uncompressed form (0x04 + x + y)
    public_key = sk.get_verifying_key().to_string('uncompressed')
    return public_key

def public_key_to_bitcoin_address(public_key):
    # Perform SHA256 on the public key
    sha256_pubkey = hashlib.sha256(public_key).digest()
    # Perform RIPEMD160 on the SHA256 hash
    ripemd160_pubkey = hashlib.new('ripemd160', sha256_pubkey).digest()
    # Add version byte (0x00 for mainnet addresses)
    versioned_payload = b'\x00' + ripemd160_pubkey
    # Perform double SHA256 to get the checksum
    checksum = hashlib.sha256(hashlib.sha256(versioned_payload).digest()).digest()[:4]
    # Concatenate versioned payload with checksum
    address = versioned_payload + checksum
    # Encode the result in Base58
    bitcoin_address = base58.b58encode(address)
    return bitcoin_address.decode('ascii')

#private_key = 0x2832ed74f2b5e35ee
private_key = 0x1a838b13505b26867

public_key = get_public_key(private_key)
bitcoin_address = public_key_to_bitcoin_address(public_key)

print("Private Key (Hex):", hex(private_key))
print("Public Key (Hex):", public_key.hex())
print("Bitcoin Address:", bitcoin_address)
