"use strict";

const menu = document.querySelector("#sidenav-explorer");
const editorGroup = document.querySelector("#editor-group");
listDir();
const elements = document.querySelectorAll("#file");
const root_code = document.querySelector("#show_code");
const $detailsList = document.querySelectorAll("details");
const CURRENT_PATH = location.pathname;

let editorTab = JSON.parse(window.localStorage.getItem('activeFiles')) || [];

elements.forEach((element) => {
    element.addEventListener("click", async (event) => {
        const filename = event.currentTarget.dataset.filename;
        const path = event.currentTarget.dataset.location;

        const response = await fetch(`${CURRENT_PATH}`, {
            method: "POST",
            headers: {
                "Content-Type": "application/json",
            },
            body: JSON.stringify({
                filename,
                path,
            }),
        });
        const data = await response.json();
        if (data.type === "code") {
            root_code.innerHTML = data.info;
        } else {
            let parse_binary = JSON.parse(data.info);
            root_code.innerHTML = `
                <img src="data:image/${parse_binary.file_ext};base64,${atob(
                parse_binary.$binary
            )}" alt="XD">
            `.trim();
        }
        if (!editorTab.find(({ _filename }) => _filename === filename)) {
            editorTab.push({
                filename,
                code: data.info,
                isActive: false,
                path,
                key: path + filename

            });
            updateEditorGroup({ isSave: true });
        }
    });
});

/**
 * @param {String} dirName
 * Nombre del directorio
 * @param { String } listOfFileOrListOfDir
 * un string con los subdirectorios y/o archivos del directorio
 * @param { Boolean } isOpen
 * Permite tener un directorio abierto en el explorador de archivos
 */
function renderTemplate(dirName, listOfFileOrListOfDir, isOpen) {
    return `
            <details ${isOpen && "open"}>
                <summary>${dirName}</summary>
                ${listOfFileOrListOfDir}
            </details>
            `;
}

/**
 * Nombres de los archivos del directorio
 * @param {Array} elements
 * @returns { String }
 */
function renderListOfFile(elements, path) {
    return `
            <div class="content">
                <ol>
                    ${elements
                        .map((content) => {
                            const ext = content.toLowerCase().split(".");
                            return `<li id="file" class="file ${
                                ext[ext.length - 1]
                            }" data-filename="${content}" data-location="${path}">${content}</li>`;
                        })
                        .join("")}
                </ol>
            </div>
            `;
}

function renderTab({ filename, path, key, isActive }) {
    return `
<div class="tab ${isActive ? 'active' : ''}" data-tab-key="${key}">
    <div class="close-tab" onclick="closeTab('${filename}')">
        <i>
            <img width="14px" src="/static/icons/close-icon.svg" alt="Cerrar archivo">
        </i>
    </div>
    <div class="filename" onclick="tabActive('${key}')">
        <p>${filename}</p>
    </div>
</div>
    `;
}

function tabActive(path) {
    console.log(path);
    const tab = document.querySelector(`[data-tab-key="${path}"]`);
    const refTab = editorTab.find(tab => tab.isActive)
    if(refTab) refTab.isActive = false;
    
    editorTab.forEach(tab => {
        if(tab.key === path) {
            tab.isActive = true
        }
    })

    tab.classList.toggle("active");
}

function closeTab(filename) {
    console.log(filename);
    editorTab = editorTab.filter((tab) => tab.filename != filename);
    updateEditorGroup();
}

function updateEditorGroup({ isSave } = { isSave: Boolean() }) {
    editorGroup.innerHTML = editorTab.map((data) => renderTab({...data})).join("");
    if(isSave) {
        window.localStorage.setItem('activeFiles', JSON.stringify(editorTab))
    }
}

function subDirs(data, index = 1) {
    var _subDirs = "";
    let dirsLength = datas.length;
    // debugger
    let relPath = data.path.split("/").slice(3).filter(Boolean);
    for (let j = index; j < dirsLength; j++) {
        let _relPath = datas[j].path.split("/").slice(3).filter(Boolean);
        if (
            datas[j].path.includes(data.path) &&
            _relPath.length === relPath.length + 1 &&
            !data.isListed
        ) {
            _subDirs += subDirs(datas[j], j);
        }
    }

    data.isListed = true;
    return renderTemplate(
        relPath[relPath.length - 1],
        _subDirs + renderListOfFile(data.files, data.path),
        false
    );
}

function listDir() {
    var dirs = "";
    let dirsLength = datas.length;
    for (let i = 0; i < dirsLength; i++) {
        if (!datas[i].isListed && !datas[i].path.endsWith(`${projectName}/`)) {
            let relPath = datas[i].path.split("/").slice(3).filter(Boolean);
            let dirName = relPath[relPath.length - 1];

            let subDir = subDirs(datas[i], i);
            dirs += subDir;
        }
    }

    const mainFiles = datas.find((value) =>
        value.path.endsWith(`${projectName}/`)
    );
    menu.innerHTML = renderTemplate(
        projectName,
        dirs + renderListOfFile(mainFiles.files, mainFiles.path),
        true
    );
}

document.addEventListener('DOMContentLoaded', () => {
    updateEditorGroup()
})
