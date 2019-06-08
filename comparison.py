from PIL import Image

source = Image.open('pizza.tif')
base = source
base.convert('RGB')
base.save('pizza-base.bmp')

bw = base
bw = bw.convert('L')
bw = bw.convert('RGB')
bw.save('pizza-bw.bmp')

rgba = base
rgba = rgba.convert('RGBA')
rgba = rgba.convert('RGB')
rgba.save('pizza-rgba.bmp')