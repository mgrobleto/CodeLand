from os import walk

directory = {}

# { 'registro_1': ['Registro Academico.C'],
#   'registro_1\DESIGNER': ['designer 6.txt', 'designer.txt', 'designer2.txt', 'designer3.txt', 'designer4.txt', 'designer5.txt']
# }

for root, dirs, files in walk('./static_projects/text_mode/registro_1'):
    for file in files:
        # Obtiene el último valor de la ruta
        # '.', 'static_projects', 'text_mode', 'registro_1'] obtiene el último
        # registro_1
        directory[root.split('/')[-1]] = files


for value in directory:
    # value es el valor de la clave del objeto: registro_1, registro_1\DESIGNER
    print(f'En el directorio {value} esta los archivos: {directory[value]}\n')