from os import walk
from pathlib import Path

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
# print(hexade.encode('utf-8').decode('utf-8'))


class DisplayablePath(object):
    display_filename_prefix_middle = '├──'
    display_filename_prefix_last = '└──'
    display_parent_prefix_middle = '    '
    display_parent_prefix_last = '│   '

    def __init__(self, path, parent_path, is_last):
        self.path = Path(str(path))
        self.parent = parent_path
        self.is_last = is_last
        if self.parent:
            self.depth = self.parent.depth + 1
        else:
            self.depth = 0

    @property
    def displayname(self):
        if self.path.is_dir():
            return self.path.name + '/'
        return self.path.name

    @classmethod
    def make_tree(cls, root, parent=None, is_last=False, criteria=None):
        root = Path(str(root))
        criteria = criteria or cls._default_criteria

        displayable_root = cls(root, parent, is_last)
        yield displayable_root

        sorted(list(path
                for path in root.iterdir()
                if criteria(path)),
                key=lambda s: str(s).lower())

        children = sorted(list(path
                               for path in root.iterdir()
                               if criteria(path)),
                          key=lambda s: str(s).lower())
        count = 1
        for path in children:
            is_last = count == len(children)
            if path.is_dir():
                yield from cls.make_tree(path,
                                         parent=displayable_root,
                                         is_last=is_last,
                                         criteria=criteria)
            else:
                yield cls(path, displayable_root, is_last)
            count += 1

    @classmethod
    def _default_criteria(cls, path):
        return True

    @property
    def displayname(self):
        if self.path.is_dir():
            return self.path.name + '/'
        return self.path.name

    def displayable(self):
        if self.parent is None:
            return self.displayname

        _filename_prefix = (self.display_filename_prefix_last
                            if self.is_last
                            else self.display_filename_prefix_middle)

        parts = ['{!s} {!s}'.format(_filename_prefix,
                                    self.displayname)]

        parent = self.parent
        while parent and parent.parent is not None:
            parts.append(self.display_parent_prefix_middle
                         if parent.is_last
                         else self.display_parent_prefix_last)
            parent = parent.parent

        return ''.join(reversed(parts))

paths = DisplayablePath.make_tree(Path('static'))

for path in paths:
    path.displayable()


# prefix components:
space =  '    '
branch = '│   '
# pointers:
tee =    '├── '
last =   '└── '

def tree(dir_path: Path, prefix: str=''):
    """A recursive generator, given a directory Path object
    will yield a visual tree structure line by line
    with each line prefixed by the same characters
    """
    contents = list(dir_path.iterdir())
    # contents each get pointers that are ├── with a final └── :
    pointers = [tee] * (len(contents) - 1) + [last]
    
    for pointer, path in zip(pointers, contents):
        # print(path)
        yield prefix + pointer + path.name
        if path.is_dir(): # extend the prefix and recurse:
            extension = branch if pointer == tee else space 
            # i.e. space because last, └── , above so no more |
            yield from tree(path, prefix=prefix+extension)

def tree2(dir_path: Path, prefix: str=''):
    """A recursive generator, given a directory Path object
    will yield a visual tree structure line by line
    with each line prefixed by the same characters
    """
    contents = list(dir_path.iterdir())
    # contents each get pointers that are ├── with a final └── :
    pointers = [tee] * (len(contents) - 1) + [last]
    
    print(len(pointers))
    for pointer, path in zip(pointers, contents):
        yield prefix + pointer + path.name
        if path.is_dir(): # extend the prefix and recurse:
            extension = branch if pointer == tee else space 
            # i.e. space because last, └── , above so no more |
            yield from tree(path, prefix=prefix+extension)

# aguacate = 1
for line in tree(Path.home() / 'project/Codeland/Codeland/static'):
    line
    # aguacate = aguacate +1
    # print(aguacate)

