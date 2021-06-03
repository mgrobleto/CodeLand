'use strict'

const $formDelete = document.querySelectorAll('#delete-project')
const $formUpdate = document.querySelector('#edit-info')
const $project = document.querySelector('#projects')
const $overlayModal = document.querySelector('#overlay-modal')
const $editmodal = document.querySelector('#custom-modal')
const $showModal = document.querySelector('#btn-modal-editar')

function renderTemplate(project) {
    return `
    <div class='col col-lg-4'>
    <div class='card' style='width: 18rem;'>
        <img src="data:image/${project.contentType};base64,${atob(project.image.$binary)}" alt="${project.title}">
        <div class='card-body'>
            <h5 class='card-title'>${project.title}</h5>
            <p class='card-text'>
                ${project.description}
            </p>
            <a href='/project/${project.author}/${project.title}' class='btn btn-primary'>Ver y editar</a>
            <form id="delete-project">
                <input type="hidden" name="id" value="${project._id.$oid}">
                <button class='btn btn-danger'>Borrar proyecto</button>
            </form>
        </div>
    </div>
</div>
    `.trim()
}

$formUpdate.addEventListener('submit', async (event) => {
    event.preventDefault()
    const formData = new FormData(event.currentTarget)
    const response = await fetch(`/update-account/${formData.get('id')}`, {
        method: 'PUT',
        body: formData
    })
    const data = await response.json()
    console.log(data)
    const { username, email, image } = data
    console.log(username, email, image)
})

$formDelete.forEach(function ($form) {
    $form.addEventListener('submit', async (event) => {
        event.preventDefault()
        const formData = new FormData(event.currentTarget)
        const response = await fetch(`/delete-project`, {
            method: 'DELETE',
            body: formData
        })
        const { data, delete_info} = await response.json()
        let code = ''
        $project.innerHTML = ''
        console.log(JSON.parse(data))
        console.log(delete_info)
        for(const project of JSON.parse(data)) {
            code += renderTemplate(project)
        }
        $project.innerHTML = code
    })
})

$showModal.addEventListener('click', () => {
    $editmodal.classList.toggle('active')
    $overlayModal.classList.toggle('active')
})

$overlayModal.addEventListener('click', () => {
    $editmodal.classList.remove('active')
    $overlayModal.classList.remove('active')
})
