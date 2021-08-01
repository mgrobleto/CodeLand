'use strict'
const $form = document.querySelector('#form')

$form.addEventListener('submit', async (e) => {
    e.preventDefault()

    const formData = new FormData(e.currentTarget)
    const projectName = formData.get('projectName')
    console.log(formData.get('project_mode'))

    const response = await fetch('/add-project', {
        method: 'POST',
        body: formData
    })
    const data = await response.json()
    const username = getCookie('username').replaceAll("\"", "")

    console.log(data)
    if (data.success) {
        window.location.href = `/project/${username}/${projectName}`
    }
    
})

function getCookie(name) {
    const value = `; ${document.cookie}`;
    const parts = value.split(`; ${name}=`);
    if (parts.length === 2) return parts.pop().split(';').shift();
}

// const $form = document.querySelector('#form')
// $form.addEventListener('submit', async event => {
//     event.preventDefault()
//     const formData = new FormData(event.currentTarget)
//     const response = await fetch('/register', {
//         method: 'POST',
//         body: formData
//     })
//     console.log(response)
//     if(response.redirected) {
//         window.location.href = response.url
//     }
// })