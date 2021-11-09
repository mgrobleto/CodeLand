'use strict'
import { alertError, alertSuccess } from './libs/alerts.js'

const $btnDeleteProject = document.querySelectorAll('.btn-delete-project')
const $formUpdate = document.querySelector('#edit-info')
const $project = document.querySelector('#projects')
const $overlayModal = document.querySelector('#overlay-modal')
const $editmodal = document.querySelector('#custom-modal')
const $showModal = document.querySelector('#btn-modal-editar')
const $btnUpdate = document.querySelector('#btn-update')
const projectCount = document.querySelector('#project-count')
const fragmentCount = document.querySelector('#fragment-count')
const $btnDeleteFragment = document.querySelectorAll('.btn-delete-fragment')

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
                <a href='/project/${project.author}/${project.project_name}' class='btn bi bi-pencil-fill'></a>
            </div>
            <div class="col-4">
                <button class="btn bi bi-trash-fill btn-delete-project" value="${project._id}"></button>
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

$btnDeleteProject.forEach(function ($btn) {
    $btn.addEventListener('click', async function () {
        const formData = new FormData()
        formData.append('id', this.value)

        this.setAttribute('disabled', true)
        const response = await fetch(`/delete-project`, {
            method: 'DELETE',
            body: formData
        })

        const result = await response.json()
        console.log(result)
        if(result.success) {
            const { data, delete_info} = result
            let code = ''
            $project.innerHTML = ''
    
            for(const project of data) {
                code += renderTemplate(project)
            }
            $project.innerHTML = code
            projectCount.innerHTML = `${projectCount.innerHTML - 1}`
            alertSuccess(`Proyecto ${delete_info.project_name}`)
        } else {
            this.removeAttribute('disabled')
            alertError(result.message)
        }
    })
})

$btnDeleteFragment.forEach(btn => {
    btn.addEventListener('click', async function() {
        const formData = new FormData()
        formData.append('id', this.value)
        console.log(this.value)
        const response = await fetch(`/delete-fragment`, {
            method: 'DELETE',
            body: formData
        })
        const data = await response.json()
        if(data.success) {
            alertSuccess('Borrado')
        } else {
            alertError(data.message)
        }
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