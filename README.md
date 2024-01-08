# hex-lexer

tool that converts hex written in plain text into raw binary

the hex values are written without the 0x prefix and are interpreted 2 characters at a time. For example: 0a0b will produce the 2 bytes 0x0a and 0x0b. If an invalid character is encountered, it is skipped. For example: "0a b 4kc  #2" will produce the 3 bytes 0a b4 and c2
