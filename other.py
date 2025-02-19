
import hashlib
import ecdsa
import base58

# Function to generate Bitcoin address from private key
def private_key_to_address(private_key_bytes):

    # Step 2: Generate the public key from the private key
    sk = ecdsa.SigningKey.from_secret_exponent(private_key_bytes, curve=ecdsa.SECP256k1)
    public_key = sk.get_verifying_key().to_string()

    # Step 3: Perform the SHA-256 hash on the public key
    sha256_public_key = hashlib.sha256(public_key).digest()

    # Step 4: Perform the RIPEMD-160 hash on the SHA-256 hash
    ripemd160 = hashlib.new('ripemd160', sha256_public_key).digest()

    # Step 5: Add version byte (0x00 for mainnet)
    versioned_payload = b'\x00' + ripemd160

    # Step 6: Perform SHA-256 hash on the versioned payload
    checksum = hashlib.sha256(hashlib.sha256(versioned_payload).digest()).digest()[:4]

    # Step 7: Concatenate versioned payload with checksum
    address_bytes = versioned_payload + checksum

    # Step 8: Encode in Base58
    return base58.b58encode(address_bytes).decode('ascii')

#private_key_bytes = 0x2832ed74f2b5e35ee
private_key_bytes = 0x1a838b13505b26867
bitcoin_address = private_key_to_address(private_key_bytes)
print("private_key_bytes:", hex(private_key_bytes))
print("Bitcoin Address:", bitcoin_address)
