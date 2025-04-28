width = 200
height = 100

# BMP и DIB заголовки
bmp_header = bytearray([
    0x42, 0x4D,             # Signature 'BM'
    0, 0, 0, 0,             # File size (will fill later)
    0, 0,                   # Reserved
    0, 0,                   # Reserved
    54, 0, 0, 0             # Offset to pixel data
])

dib_header = bytearray([
    40, 0, 0, 0,            # Header size
    width & 0xFF, (width >> 8) & 0xFF, 0, 0,  # Width
    height & 0xFF, (height >> 8) & 0xFF, 0, 0,  # Height
    1, 0,                  # Color planes
    24, 0,                 # Bits per pixel
    0, 0, 0, 0,            # Compression
    0, 0, 0, 0,            # Image size (can be zero for no compression)
    0x13, 0x0B, 0, 0,      # X pixels per meter
    0x13, 0x0B, 0, 0,      # Y pixels per meter
    0, 0, 0, 0,            # Total colors
    0, 0, 0, 0             # Important colors
])

# Пиксельные данные
row_padding = (4 - (width * 3) % 4) % 4
row_size = width * 3 + row_padding
pixel_data = bytearray()

for y in range(height):
    row = bytearray()
    for x in range(width):
        if (x == width // 2 and y == height // 2):
            row += bytes([255, 0, 0])   # Синяя точка
        elif (x == width // 2 + 10 and y == height // 2):
            row += bytes([0, 255, 0])   # Зелёная точка
        elif (x == width // 2 - 10 and y == height // 2):
            row += bytes([0, 0, 255])   # Красная точка
        else:
            row += bytes([255, 255, 255])  # Белый фон
    row += bytes(row_padding)  # Добавляем паддинг
    pixel_data = row + pixel_data  # BMP сохраняет снизу вверх!

# Теперь размер файла
file_size = 54 + len(pixel_data)
bmp_header[2] = file_size & 0xFF
bmp_header[3] = (file_size >> 8) & 0xFF
bmp_header[4] = (file_size >> 16) & 0xFF
bmp_header[5] = (file_size >> 24) & 0xFF

# Сохраняем
with open("input.bmp", "wb") as f:
    f.write(bmp_header)
    f.write(dib_header)
    f.write(pixel_data)
