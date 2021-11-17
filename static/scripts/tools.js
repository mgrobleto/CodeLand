const btnDownload = document.getElementById('download-btn');
const btnContainer = document.querySelector('.turbo-description');

btnDownload.addEventListener('click', async () => {
    console.log('download');
    const progress = setProgressBar(btnContainer, '70');
    const response = await fetch('/tools/downloadTurboC')
    const data = await response.blob();
    progress.setAttribute('value', '100');
    const url = URL.createObjectURL(data);
    const a = document.createElement('a');
    a.href = url;
    a.download = 'TurboC.exe';
    a.style = 'display: none';
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
    document.body.removeChild(progress);
})

function btn($container) {
    const button = document.createElement('button');
    button.setAttribute('id', 'download-btn');
    button.textContent = 'Descargar';
    $container.appendChild(button);
}

function setProgressBar($container, percent) {
    const progressBar = document.createElement('progress');
    progressBar.setAttribute('max', '100');
    progressBar.setAttribute('value', percent);
    progressBar.style.height = '10px';
    progressBar.style.backgroundColor = '#00bcd4';
    progressBar.style.borderRadius = '5px';
    progressBar.style.marginTop = '10px';
    $container.appendChild(progressBar);
    return progressBar;
}
