pipeline {
    agent {
        docker {
            image 'ghcr.io/anothersimplecoder/dockerxx_linux_x86_64:latest'
            args '-u root'
        }
    }

    stages {
        stage('Set up build environment') {
            sh 'mkdir build'
            
            dir('build') {
                sh 'cmake ..'
            }
        }

        stage('Build') {
            dir('build') {
                sh 'cmake --build .'
            }
        }
    }
}