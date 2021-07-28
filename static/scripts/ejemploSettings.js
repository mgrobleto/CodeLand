const openInfo = document.getElementById("open-info");
const openExplorer = document.getElementById("open-explorer");
const openDownload = document.getElementById("open-download");
const copyCode = document.getElementById("copy-code");
const menuOptions = document.querySelector("#menu-options");
const $backItem = document.querySelector('#back-history')

copyCode.addEventListener("click", copyToClipboard);

function copyToClipboard(element) {
    const code = document.querySelector('#show_code')
    const codeText = code.innerText;
    if(codeText.length > 0) {
        navigator.clipboard.writeText(codeText).then(() => {
            element.innerText = "Copied!";
            setTimeout(() => {
                element.innerText = "Copy to clipboard";
            }, 2000);
        }).catch((e) => {
            console.error(e);
        })
    }
    console.log('xD')
}

$backItem.addEventListener("click", () => {
    history.back();
});

function changeOptionMenu(classElement) {
    if(!this.classList.contains("is-active")) {
        const options = document.querySelectorAll(classElement)
        if(options.length > 0) {
            options.forEach(function(option) {
                option.classList.remove("is-active");
            });
            menuOptions.classList.toggle("is-active")
        }
        this.classList.add("is-active");
    } else {
        this.classList.remove("is-active");
    }
}



openInfo.addEventListener("click", function () {
    const infoEditor = document.querySelector('.info-option-container')
    changeOptionMenu.bind(this)(".open-option-menu.is-active");
    changeOptionMenu.bind(infoEditor)(".menu-option");
});

openExplorer.addEventListener("click", function () {
    const explorerEditor = document.querySelector('.explorer-option-container')
    changeOptionMenu.bind(this)(".open-option-menu.is-active");
    changeOptionMenu.bind(explorerEditor)(".menu-option");
});

openDownload.addEventListener("click", function () {
    const downloadEditor = document.querySelector('.download-option-container')
    changeOptionMenu.bind(this)(".open-option-menu.is-active");
    changeOptionMenu.bind(downloadEditor)(".menu-option");
});
