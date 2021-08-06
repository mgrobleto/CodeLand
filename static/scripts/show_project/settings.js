const openInfo = document.getElementById("open-info");
const openExplorer = document.getElementById("open-explorer");
const openGithub = document.getElementById("open-github");
const openSettings = document.getElementById("open-settings");
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
            // menuOptions.classList.toggle("is-active")
        }
        this.classList.add("is-active");
    } else {
        this.classList.remove("is-active");
    }
}

function optionsAnimate(currentOpenOption) {
    const options = [...document.querySelectorAll(".open-option-menu")];
    if(options.length > 0) {
        const isActive = options.find(option => option.classList.contains('is-active'));

        if(!isActive) {
            menuOptions.classList.remove("is-active");
        } else if(isActive.classList.contains('is-active') && isActive === currentOpenOption) {
            menuOptions.classList.add("is-active");
        } else if(!isActive.classList.contains('is-active') && isActive === currentOpenOption) {
            menuOptions.classList.remove("is-active");
        } else if(isActive !== currentOpenOption) {
            menuOptions.classList.add("is-active");
        }
    }
}

openInfo.addEventListener("click", function () {
    const infoEditor = document.querySelector('.info-option-container')
    changeOptionMenu.bind(this)(".open-option-menu.is-active");
    changeOptionMenu.bind(infoEditor)(".menu-option");
    optionsAnimate(this)
});

openExplorer.addEventListener("click", function () {
    const explorerEditor = document.querySelector('.explorer-option-container')
    changeOptionMenu.bind(this)(".open-option-menu.is-active");
    changeOptionMenu.bind(explorerEditor)(".menu-option");
    optionsAnimate(this)
});

openGithub.addEventListener("click", function () {
    const githubEditor = document.querySelector('.github-option-container')
    changeOptionMenu.bind(this)(".open-option-menu.is-active");
    changeOptionMenu.bind(githubEditor)(".menu-option");
    optionsAnimate(this)
});

openSettings.addEventListener("click", function () {
    const settingsEditor = document.querySelector('.settings-option-container')
    changeOptionMenu.bind(this)(".open-option-menu.is-active");
    changeOptionMenu.bind(settingsEditor)(".menu-option");
    optionsAnimate(this)
});

openDownload.addEventListener("click", function () {
    const downloadEditor = document.querySelector('.download-option-container')
    changeOptionMenu.bind(this)(".open-option-menu.is-active");
    changeOptionMenu.bind(downloadEditor)(".menu-option");
    optionsAnimate(this)
});
