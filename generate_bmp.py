with open("input.bmp", "wb") as f:
    f.write(
        bytes.fromhex(
            # BMP Header (14 bytes)
            "42 4D"        # Signature "BM"
            "3E 00 00 00"  # File size = 62 bytes
            "00 00"        # Reserved
            "00 00"        # Reserved
            "36 00 00 00"  # Offset to pixel data = 54

            # DIB Header (40 bytes)
            "28 00 00 00"  # DIB header size = 40 bytes
            "02 00 00 00"  # Width = 2
            "02 00 00 00"  # Height = 2
            "01 00"        # Color planes = 1
            "18 00"        # Bits per pixel = 24
            "00 00 00 00"  # Compression = 0
            "08 00 00 00"  # Image size = 8 bytes
            "13 0B 00 00"  # X pixels per meter
            "13 0B 00 00"  # Y pixels per meter
            "00 00 00 00"  # Colors in palette
            "00 00 00 00"  # Important colors

            # Pixel data (2x2 pixels, bottom-up, BGR, each row padded to 4 bytes)
            "FF 00 00 00"  # Red (with 1 byte padding)
            "00 FF 00 00"  # Green (with 1 byte padding)
            "00 00 FF 00"  # Blue (with 1 byte padding)
            "FF FF FF 00"  # White (with 1 byte padding)
        )
    )
