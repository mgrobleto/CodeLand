import { ListDirTemplate } from "../listDirUI/templates.js";

class ListDir extends ListDirTemplate {
    data = [];
    
    constructor(data, projectName) {
        super();
        this.data = data;
        this.projectName = projectName;
        this.listDir = [];
        this.menu = document.querySelector("#sidenav-explorer");

        if(ListDir._instance) {
            return ListDir._instance
        }
        console.log('xD')
        ListDir._instance = this;
    }

    // Get list of files and folders
    renderList() {
        var dirs = [];
        const fragment = document.createDocumentFragment();
        let dirsLength = this.data.length;

        for (let i = 0; i < dirsLength; i++) {
            if (
                !this.data[i].isListed &&
                !this.data[i].path.endsWith(`${this.projectName}/`)
            ) {
                let subDir = this.subDirs(this.data[i], i);
                dirs.push(subDir);
            }
        }

        const mainFiles = this.data.find((value) =>
            value.path.endsWith(`${this.projectName}/`)
        );

        fragment.append(...dirs, this.listOfFileDOM(mainFiles.files, mainFiles.path));

        this.menu.appendChild(this.containerFilesDOM(
            this.projectName,
            fragment,
            true
        ));
    }

    subDirs(data, index = 1) {
        var _subDirs = [];
        const fragment = document.createDocumentFragment();
        let dirsLength = this.data.length;
        // debugger
        let relPath = data.path.split("/").slice(3).filter(Boolean);
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
        fragment.append(..._subDirs, this.listOfFileDOM(data.files, data.path));

        return this.containerFilesDOM(
            relPath[relPath.length - 1],
            fragment,
            false
        );
    }
}


export default ListDir;