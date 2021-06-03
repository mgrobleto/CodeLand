from os import listdir, path

directory = []
for direct in listdir('./'):
    if path.isdir(direct):
        directory.append(direct)

print(directory)
