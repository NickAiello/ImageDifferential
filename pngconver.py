from PIL import Image
import sys
import re

name = sys.argv[1]

source = Image.open(name)
name = re.sub(r"\.[^\.]+$",'',name)
base = source
base.save(name+'.png')
