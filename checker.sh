#!/bin/bash

# Path to the executable
APP="./app"

# Path to the file containing keys
KEYS_FILE="KEYS.txt"

# Message to encrypt and decrypt
MESSAGE="cryptomonede"

# Loop through each key in the KEYS_FILE
while IFS= read -r key; do
    
    
    # Decrypt the encrypted result with the current key and store the result
    decrypted_result="$($APP "$key")"

    # Compare the decrypted result with the original message
    if [ "$decrypted_result" != "$MESSAGE" ]; then
        echo "Error: Key $key does not produce correct decryption"
    fi
done < "$KEYS_FILE"
