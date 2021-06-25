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


# for value in directory:
#     value es el valor de la clave del objeto: registro_1, registro_1\DESIGNER
#     print(f'En el directorio {value} esta los archivos: {directory[value]}\n')

INVALID_FILENAME = {':', '*', '/', '"', '?', '>', '|', '<'}

def check_folder_name(string):
    for invalid_name in INVALID_FILENAME:
        if string.find(invalid_name) > -1:
            string = string.replace(invalid_name, '_')
    return string

# print(check_folder_name('Hola *:D'))
hexade = u"static_project/text_mode/Simulaci\u00f3n Loter\u00eda/"
print(hexade.encode('utf-8').decode('utf-8'))