pipeline {
    agent {
        docker {
            image 'ghcr.io/anothersimplecoder/dockerxx_linux_x86_64:latest'
            args '-u root'
        }
    }

    stages {
        stage('Set up build environment') {
            steps {
                sh 'mkdir build'
            
                dir('build') {
                    sh 'cmake ..'
                }
            }
        }

        stage('Build') {
            steps {
                dir('build') {
                    sh 'cmake --build .'
                }
            }
        }
    }
}