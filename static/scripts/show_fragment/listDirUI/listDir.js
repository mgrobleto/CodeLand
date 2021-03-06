import { ListDirTemplate } from "../listDirUI/templates.js";

class ListDir extends ListDirTemplate {
    data = [];
    
    constructor(data, fragmentName, depth, isOwner) {
        super();
        this.data = data;
        this.fragmentName = fragmentName;
        this.depth = depth;
        this.listDir = [];
        this.menu = document.querySelector("#explorer-editor");
        this.isOwner = isOwner;

        if(ListDir._instance) {
            return ListDir._instance
        }
        ListDir._instance = this;
    }

    // Get list of files and folders
    renderList() {
        var dirs = [];
        const fragment = new DocumentFragment();
        let dirsLength = this.data.length;

        for (let i = 0; i < dirsLength; i++) {
            if (
                !this.data[i].isListed &&
                !this.data[i].path.endsWith(`${this.fragmentName}/`)
            ) {
                let subDir = this.subDirs(this.data[i], i);
                dirs.push(subDir);
            }
        }

        const mainFiles = this.data.find((value) =>
            value.path.endsWith(`${this.fragmentName}/`)
        );
        if(mainFiles) {
            fragment.append(...dirs, this.listOfFileDOM(mainFiles.files, mainFiles.path, this.isOwner, 'mainFiles'));
        } else {
            fragment.append(...dirs);
        }

        this.menu.appendChild(this.template(fragment, this.isOwner))
    }

    subDirs(data, index = 1) {
        var _subDirs = [];
        const fragment = new DocumentFragment();
        let dirsLength = this.data.length;
        // debugger
        let relPath = data.path.split("/").slice(this.depth).filter(Boolean);
        for (let j = index; j < dirsLength; j++) {
            let _relPath = this.data[j].path.split("/").slice(3).filter(Boolean);
            if (
                this.data[j].path.includes(data.path) &&
                _relPath.length === relPath.length + 1 &&
                !data.isListed
            ) {
                _subDirs.push(this.subDirs(this.data[j], j))
            }
        }
    
        data.isListed = true;
        fragment.append(..._subDirs, this.listOfFileDOM(data.files, data.path, this.isOwner));

        return this.containerFilesDOM(
            relPath[relPath.length - 1],
            data.path,
            fragment,
            false,
            this.isOwner
        );
    }
}


export default ListDir;