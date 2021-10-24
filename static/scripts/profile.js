'use strict'
import { alertError, alertSuccess } from './libs/alerts.js'

const $formDeleteProject = document.querySelectorAll('#delete-project')
const $formUpdate = document.querySelector('#edit-info')
const $project = document.querySelector('#projects')
const $overlayModal = document.querySelector('#overlay-modal')
const $editmodal = document.querySelector('#custom-modal')
const $showModal = document.querySelector('#btn-modal-editar')
const $btnUpdate = document.querySelector('#btn-update')
const projectCount = document.querySelector('#project-count')
const fragmentCount = document.querySelector('#fragment-count')

function renderTemplate(project) {
    return `
    <div class='card' style='width: 18rem;'>
        <img src="${project.image}" alt="${project.title}">
        <div class='card-body'>
            <h5 class='card-title'>${project.project_name}</h5>
            <p class='card-text'>
            ${project.description}
            </p>
        <div class="d-flex" id="project-main-container">
            <div class="col-4">
                <a href='/project/${user.username}/${project.project_name}' class='btn bi bi-pencil-fill'></a>
            </div>
            <div class="col-4">
                <form id="delete-project">
                    <input type="hidden" name="id" value="${project._id}">
                    <button class="btn bi bi-trash-fill btn-delete"></button>
                </form>
            </div>
            <div class="col-4">
                <a class='btn bi bi-file-arrow-down-fill' href="/download-project/${project._id}" download></a>
            </div>
        </div>
        
    </div>
</div>
    `.trim()
}

$formUpdate.addEventListener('submit', async (event) => {
    event.preventDefault()
    const formData = new FormData(event.currentTarget)
    $btnUpdate.innerHTML = 'Cargando...'
    $btnUpdate.disabled = true
    
    const response = await fetch(`/update-account/${formData.get('id')}`, {
        method: 'PUT',
        body: formData
    })
    const data = await response.json()
    console.log(data)
    if(data.success) {
        const { username, email, image } = data
        console.log(username, email, image)
        alertSuccess('Datos actualizados, las fotos de perfil tardan un tiempo en actualizarse')
        setTimeout(() => {
            window.location.reload()
        }, 1500)
    } else {
        $btnUpdate.innerHTML = 'Actualizar'
        $btnUpdate.disabled = false
        alertError(data.message)
    }
})

$formDeleteProject.forEach(function ($form) {
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

        for(const project of data) {
            code += renderTemplate(project)
        }
        $project.innerHTML = code
        projectCount.innerHTML = projectCount.innerHTML - 1
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