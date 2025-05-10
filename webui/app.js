// API Service Layer
// Login System Functionality
const loginSystem = {
    init() {
        // Check if user is already logged in
        const isLoggedIn = localStorage.getItem('aurai_logged_in');
        
        // If not logged in, create and show the login page
        if (isLoggedIn !== 'true') {
            this.showLoginPage();
        } else {
            // User is logged in, show the main content
            document.querySelector('.container').style.display = 'flex';
            
            // Initialize the app
            this.initializeApp();
        }
    },
    
    showLoginPage() {
        // Hide the main container
        document.querySelector('.container').style.display = 'none';
        
        // Create the login container if it doesn't exist
        if (!document.getElementById('login-container')) {
            const loginContainer = document.createElement('div');
            loginContainer.id = 'login-container';
            loginContainer.className = 'login-container';
            loginContainer.innerHTML = `
                <div class="animated-background">
                    <div class="circle"></div>
                    <div class="circle"></div>
                    <div class="circle"></div>
                </div>
                <div class="login-box">
                    <div class="login-header">
                        <div class="aurai-logo">
                            <i class="fas fa-brain"></i>
                            <h1>AURAI</h1>
                        </div>
                        <div class="acronym">Advanced Understanding & Responsive AI Instruction</div>
                    </div>
                    <div class="login-form">
                        <div class="welcome-message">
                            <h2>Welcome to AURAI</h2>
                            <p>Enter your credentials to access the AI Tutoring CRM system</p>
                        </div>
                        <div class="form-group">
                            <label for="username">Username</label>
                            <div class="input-wrapper">
                                <i class="fas fa-user"></i>
                                <input type="text" id="username" placeholder="Enter your username">
                            </div>
                        </div>
                        <div class="form-group">
                            <label for="password">Password</label>
                            <div class="input-wrapper">
                                <i class="fas fa-lock"></i>
                                <input type="password" id="password" placeholder="Enter your password">
                            </div>
                            <div id="error-message" class="error-message">Invalid username or password</div>
                        </div>
                        <button id="login-btn" class="login-btn">Sign In</button>
                    </div>
                </div>
            `;
            
            document.body.appendChild(loginContainer);
            
            // Add login styles to the head
            this.addLoginStyles();
            
            // Add login event handlers
            this.setupLoginEvents();
        } else {
            // If it exists just show it
            document.getElementById('login-container').style.display = 'flex';
        }
    },
    
    setupLoginEvents() {
        // Handle login button click
        document.getElementById('login-btn').addEventListener('click', () => this.handleLogin());
        
        // Handle Enter key press in password field
        document.getElementById('password').addEventListener('keypress', (e) => {
            if (e.key === 'Enter') {
                this.handleLogin();
            }
        });
    },
    
    handleLogin() {
        const username = document.getElementById('username').value;
        const password = document.getElementById('password').value;
        
        if (username === 'admin' && password === 'admin123') {
            // Store login state in local storage
            localStorage.setItem('aurai_logged_in', 'true');
            this.hideLoginPage();
            
            // Show welcome toast notification
            Toast.success('Welcome to AURAI CRM System');
        } else {
            // Show error message
            const errorMessage = document.getElementById('error-message');
            errorMessage.style.display = 'block';
            
            // Shake the inputs
            const inputs = document.querySelectorAll('.form-group input');
            inputs.forEach(input => {
                input.style.borderColor = 'var(--danger)';
                setTimeout(() => {
                    input.style.borderColor = 'var(--border-color)';
                }, 1000);
            });
        }
    },
    
    hideLoginPage() {
        // Hide login container and show main content
        document.getElementById('login-container').style.display = 'none';
        document.querySelector('.container').style.display = 'flex';
        
        // Initialize the app
        this.initializeApp();
    },
    
    addLoginStyles() {
        // Only add styles if they don't already exist
        if (!document.getElementById('login-styles')) {
            const style = document.createElement('style');
            style.id = 'login-styles';
            style.textContent = `
                .login-container {
                    display: flex;
                    position: fixed;
                    top: 0;
                    left: 0;
                    width: 100%;
                    height: 100%;
                    background: var(--background);
                    z-index: 9999;
                    justify-content: center;
                    align-items: center;
                }

                .login-box {
                    width: 400px;
                    background: var(--card-background);
                    border-radius: var(--radius);
                    box-shadow: var(--shadow-lg);
                    overflow: hidden;
                    animation: fadeIn 0.5s ease-out;
                }

                .login-header {
                    background: var(--primary-gradient);
                    padding: 2rem;
                    text-align: center;
                    color: white;
                }

                .aurai-logo {
                    display: flex;
                    align-items: center;
                    justify-content: center;
                    margin-bottom: 1rem;
                }

                .aurai-logo i {
                    font-size: 2.5rem;
                    margin-right: 1rem;
                }

                .aurai-logo h1 {
                    font-family: var(--font-heading);
                    font-size: 2.5rem;
                    margin: 0;
                }

                .login-form {
                    padding: 2rem;
                }

                .welcome-message {
                    text-align: center;
                    margin-bottom: 1.5rem;
                    animation: fadeIn 0.5s ease-out;
                }

                .welcome-message h2 {
                    font-family: var(--font-heading);
                    font-size: 1.5rem;
                    color: var(--dark);
                    margin-bottom: 0.5rem;
                }

                .welcome-message p {
                    color: var(--secondary);
                    font-size: 0.9rem;
                }

                .error-message {
                    color: var(--danger);
                    font-size: 0.9rem;
                    margin-top: 0.5rem;
                    display: none;
                    animation: shake 0.5s;
                }

                .login-btn {
                    display: block;
                    width: 100%;
                    padding: 0.75rem;
                    background: var(--primary-gradient);
                    color: white;
                    border: none;
                    border-radius: var(--radius);
                    font-family: var(--font-heading);
                    font-size: 1rem;
                    font-weight: 500;
                    cursor: pointer;
                    transition: var(--transition);
                }

                .login-btn:hover {
                    background: var(--primary-dark);
                    transform: translateY(-2px);
                    box-shadow: var(--shadow);
                }

                .animated-background {
                    position: absolute;
                    top: 0;
                    left: 0;
                    width: 100%;
                    height: 100%;
                    z-index: -1;
                    overflow: hidden;
                }

                .circle {
                    position: absolute;
                    border-radius: 50%;
                    background: linear-gradient(135deg, rgba(59, 130, 246, 0.1), rgba(37, 99, 235, 0.1));
                    animation: float 8s infinite ease-in-out alternate;
                }

                .circle:nth-child(1) {
                    width: 300px;
                    height: 300px;
                    top: -150px;
                    left: -100px;
                    animation-delay: 0s;
                }

                .circle:nth-child(2) {
                    width: 200px;
                    height: 200px;
                    top: 50%;
                    right: -100px;
                    animation-delay: 2s;
                }

                .circle:nth-child(3) {
                    width: 150px;
                    height: 150px;
                    bottom: -50px;
                    left: 30%;
                    animation-delay: 1s;
                }

                @keyframes fadeIn {
                    from { opacity: 0; transform: translateY(-20px); }
                    to { opacity: 1; transform: translateY(0); }
                }

                @keyframes shake {
                    0%, 100% { transform: translateX(0); }
                    10%, 30%, 50%, 70%, 90% { transform: translateX(-5px); }
                    20%, 40%, 60%, 80% { transform: translateX(5px); }
                }

                @keyframes float {
                    0% { transform: translateY(0) rotate(0deg); }
                    100% { transform: translateY(-20px) rotate(10deg); }
                }

                /* Responsive adjustments */
                @media (max-width: 576px) {
                    .login-box {
                        width: 90%;
                    }

                    .aurai-logo i {
                        font-size: 2rem;
                    }

                    .aurai-logo h1 {
                        font-size: 2rem;
                    }

                    .login-header, .login-form {
                        padding: 1.5rem;
                    }
                }
            `;
            
            document.head.appendChild(style);
        }
    },
    
    // Add logout functionality
    setupLogoutButton() {
        // Get the user menu in the header
        const userMenu = document.querySelector('.user-menu');
        
        // Check if logout button already exists
        if (!document.getElementById('logout-btn')) {
            // Create logout button
            const logoutBtn = document.createElement('button');
            logoutBtn.id = 'logout-btn';
            logoutBtn.className = 'btn-link';
            logoutBtn.innerHTML = '<i class="fas fa-sign-out-alt"></i> Logout';
            
            // Add click event
            logoutBtn.addEventListener('click', () => {
                // Clear the login state
                localStorage.removeItem('aurai_logged_in');
                
                // Show the login page
                this.showLoginPage();
                
                // Reset form fields
                if (document.getElementById('username')) {
                    document.getElementById('username').value = '';
                }
                if (document.getElementById('password')) {
                    document.getElementById('password').value = '';
                }
                if (document.getElementById('error-message')) {
                    document.getElementById('error-message').style.display = 'none';
                }
            });
            
            // Insert it before the username span
            const usernameSpan = userMenu.querySelector('.user-name');
            userMenu.insertBefore(logoutBtn, usernameSpan);
        }
    },
    
    // Initialize application after successful login
    initializeApp() {
        // Add logout button to the header
        this.setupLogoutButton();
        
        // Load dashboard data
        loadClients();
        loadTutors();
        loadSessions();
        loadMaterials();
        loadAIModels();
        
        // Initialize search functionality
        initializeSearchFunctionality();
        
        // Add export buttons
        addExportButtons();
        
        // Update dashboard data
        updateDashboard();
        
        // Set today as the minimum date for session scheduling
        const today = new Date().toISOString().split('T')[0];
        const sessionDateInput = document.getElementById('sessionDate');
        if (sessionDateInput) {
            sessionDateInput.min = today;
        }
        
        // Animate AURAI logo
        setTimeout(animateAuraiLetters, 500);
    }
};

// Initialize the login system when the DOM is loaded
document.addEventListener('DOMContentLoaded', function() {
    // Initialize login system
    loginSystem.init();
});
const apiService = {
    baseUrl: 'https://localhost:8080/api',
    mockMode: true, // Set to false when your backend is ready

    // Client API methods
    async getClients() {
        if (this.mockMode) {
            console.log('Using mock clients data');
            return clients || [];
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/clients`);
            if (!response.ok) throw new Error('Failed to fetch clients');
            return await response.json();
        } catch (error) {
            console.error('Error fetching clients:', error);
            throw error;
        }
    },

    async searchClients(query, searchType = 'name') {
        if (this.mockMode) {
            console.log('Searching clients in mock mode', query, searchType);
            
            // Convert query to lowercase for case-insensitive search
            const lowerQuery = query.toLowerCase().trim();
            
            return clients.filter(client => {
                switch(searchType) {
                    case 'name':
                        return `${client.firstName} ${client.lastName}`.toLowerCase().includes(lowerQuery);
                    case 'email':
                        return client.email.toLowerCase().includes(lowerQuery);
                    case 'company':
                        return (client.company || '').toLowerCase().includes(lowerQuery);
                    default:
                        return false;
                }
            });
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/clients/search`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ query, searchType })
            });

            if (!response.ok) throw new Error('Failed to search clients');
            return await response.json();
        } catch (error) {
            console.error('Error searching clients:', error);
            throw error;
        }
    },

    async getClientById(clientId) {
        if (this.mockMode) {
            console.log('Using mock client data');
            return clients.find(c => c.clientId === clientId) || null;
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/clients/${clientId}`);
            if (!response.ok) throw new Error('Failed to fetch client');
            return await response.json();
        } catch (error) {
            console.error(`Error fetching client ${clientId}:`, error);
            throw error;
        }
    },

    async addClient(clientData) {
        if (this.mockMode) {
            console.log('Adding mock client', clientData);
            // Generate a new ID
            const newId = clients.length > 0 
                ? Math.max(...clients.map(c => c.clientId)) + 1 
                : 1;
            
            const newClient = {
                ...clientData,
                clientId: newId,
                registrationDate: new Date().toISOString().split('T')[0],
                sessionsCompleted: 0
            };
            
            clients.push(newClient);
            return newClient;
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/clients/add`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(clientData)
            });

            if (!response.ok) throw new Error('Failed to add client');
            return await response.json();
        } catch (error) {
            console.error('Error adding client:', error);
            throw error;
        }
    },

    async updateClient(clientId, clientData) {
        if (this.mockMode) {
            console.log('Updating mock client', clientId, clientData);
            const index = clients.findIndex(c => c.clientId === clientId);
            if (index === -1) throw new Error('Client not found');
            
            clients[index] = {
                ...clients[index],
                ...clientData,
                clientId  // Ensure ID doesn't change
            };
            
            return clients[index];
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/clients/${clientId}/update`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(clientData)
            });

            if (!response.ok) throw new Error('Failed to update client');
            return await response.json();
        } catch (error) {
            console.error(`Error updating client ${clientId}:`, error);
            throw error;
        }
    },

    async deleteClient(clientId) {
        if (this.mockMode) {
            console.log('Deleting mock client', clientId);
            const index = clients.findIndex(c => c.clientId === clientId);
            if (index === -1) throw new Error('Client not found');
            
            clients.splice(index, 1);
            return { success: true, message: 'Client deleted' };
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/clients/${clientId}/delete`, {
                method: 'POST'
            });

            if (!response.ok) throw new Error('Failed to delete client');
            return await response.json();
        } catch (error) {
            console.error(`Error deleting client ${clientId}:`, error);
            throw error;
        }
    },

    // Tutor API methods
    async getTutors() {
        if (this.mockMode) {
            console.log('Using mock tutors data');
            return tutors || [];
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/tutors`);
            if (!response.ok) throw new Error('Failed to fetch tutors');
            return await response.json();
        } catch (error) {
            console.error('Error fetching tutors:', error);
            throw error;
        }
    },

    async addTutor(tutorData) {
        if (this.mockMode) {
            console.log('Adding mock tutor', tutorData);
            // Generate a new ID
            const newId = tutors.length > 0 
                ? Math.max(...tutors.map(t => t.userId)) + 1 
                : 1;
            
            const newTutor = {
                ...tutorData,
                userId: newId,
                sessionsCompleted: 0,
                averageRating: 0
            };
            
            tutors.push(newTutor);
            return newTutor;
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/tutors/add`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(tutorData)
            });

            if (!response.ok) throw new Error('Failed to add tutor');
            return await response.json();
        } catch (error) {
            console.error('Error adding tutor:', error);
            throw error;
        }
    },

    async deleteTutor(tutorId) {
        if (this.mockMode) {
            console.log('Deleting mock tutor', tutorId);
            const index = tutors.findIndex(t => t.userId === tutorId);
            if (index === -1) throw new Error('Tutor not found');
            
            tutors.splice(index, 1);
            return { success: true, message: 'Tutor deleted' };
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/tutors/${tutorId}/delete`, {
                method: 'POST'
            });

            if (!response.ok) throw new Error('Failed to delete tutor');
            return await response.json();
        } catch (error) {
            console.error(`Error deleting tutor ${tutorId}:`, error);
            throw error;
        }
    },

    async updateTutor(tutorId, tutorData) {
        if (this.mockMode) {
            console.log('Updating mock tutor', tutorId, tutorData);
            const index = tutors.findIndex(t => t.userId === tutorId);
            if (index === -1) throw new Error('Tutor not found');
            
            tutors[index] = {
                ...tutors[index],
                ...tutorData,
                userId: tutorId  // Ensure ID doesn't change
            };
            
            return tutors[index];
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/tutors/${tutorId}/update`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(tutorData)
            });

            if (!response.ok) throw new Error('Failed to update tutor');
            return await response.json();
        } catch (error) {
            console.error(`Error updating tutor ${tutorId}:`, error);
            throw error;
        }
    },

    // Session API methods  
    async getSessions() {
        if (this.mockMode) {
            console.log('Using mock sessions data');
            return sessions || [];
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/sessions`);
            if (!response.ok) throw new Error('Failed to fetch sessions');
            return await response.json();
        } catch (error) {
            console.error('Error fetching sessions:', error);
            throw error;
        }
    },

    async addSession(sessionData) {
    if (this.mockMode) {
        console.log('Adding mock session', sessionData);
        // Generate a new ID
        const newId = sessions.length > 0 
            ? Math.max(...sessions.map(s => s.sessionId)) + 1 
            : 1;
        
        const newSession = {
            ...sessionData,
            sessionId: newId,
            status: 'Scheduled',
            aiModelIds: [],
            sessionCost: calculateSessionCost(sessionData)
        };
        
        sessions.push(newSession);
        updateSessionCounts(); // Update counts after adding session
        return newSession;
    }
    
    try {
        const response = await fetch(`${this.baseUrl}/sessions/add`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(sessionData)
        });

        if (!response.ok) throw new Error('Failed to add session');
        const result = await response.json();
        updateSessionCounts(); // Update counts after adding session
        return result;
    } catch (error) {
        console.error('Error adding session:', error);
        throw error;
    }
},

    async cancelSession(sessionId) {
        if (this.mockMode) {
            console.log('Canceling mock session', sessionId);
            const index = sessions.findIndex(s => s.sessionId === sessionId);
            if (index === -1) throw new Error('Session not found');
            
            sessions[index].status = 'Cancelled';
            return { success: true, message: 'Session cancelled' };
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/sessions/${sessionId}/cancel`, {
                method: 'POST'
            });

            if (!response.ok) throw new Error('Failed to cancel session');
            return await response.json();
        } catch (error) {
            console.error(`Error canceling session ${sessionId}:`, error);
            throw error;
        }
    },

    async function(sessionId, sessionData) {
        console.log('Updating session:', sessionId, sessionData);
        
        if (this.mockMode) {
            // In mock mode, update the session in the local array
            const index = sessions.findIndex(s => s.sessionId === parseInt(sessionId));
            if (index === -1) {
                console.error('Session not found');
                throw new Error('Session not found');
            }
            
            sessions[index] = {
                ...sessions[index],
                ...sessionData
            };
            
            console.log('Updated session:', sessions[index]);
            return sessions[index];
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/sessions/${sessionId}`, {
                method: 'PUT',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(sessionData)
            });
            
            if (!response.ok) {
                const errorText = await response.text();
                console.error('API error:', errorText);
                throw new Error(`API error: ${response.status} ${errorText}`);
            }
            
            return await response.json();
        } catch (error) {
            console.error('Error updating session:', error);
            throw error;
        }
    },

    // Materials API methods
    async getMaterials() {
        if (this.mockMode) {
            console.log('Using mock materials data');
            return materials || [];
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/materials`);
            if (!response.ok) throw new Error('Failed to fetch materials');
            return await response.json();
        } catch (error) {
            console.error('Error fetching materials:', error);
            throw error;
        }
    },

    async addMaterial(materialData) {
        if (this.mockMode) {
            console.log('Adding mock material', materialData);
            // Generate a new ID
            const newId = materials.length > 0 
                ? Math.max(...materials.map(m => m.materialId)) + 1 
                : 1;
            
            const newMaterial = {
                ...materialData,
                materialId: newId,
                rating: 0,
                usageCount: 0
            };
            
            materials.push(newMaterial);
            return newMaterial;
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/materials/add`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(materialData)
            });

            if (!response.ok) throw new Error('Failed to add material');
            return await response.json();
        } catch (error) {
            console.error('Error adding material:', error);
            throw error;
        }
    },

    async updateMaterial(materialId, materialData) {
        if (this.mockMode) {
            console.log('Updating mock material', materialId, materialData);
            const index = materials.findIndex(m => m.materialId === materialId);
            if (index === -1) throw new Error('Material not found');
            
            materials[index] = {
                ...materials[index],
                ...materialData,
                materialId  // Ensure ID doesn't change
            };
            
            return materials[index];
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/materials/${materialId}/update`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(materialData)
            });

            if (!response.ok) throw new Error('Failed to update material');
            return await response.json();
        } catch (error) {
            console.error(`Error updating material ${materialId}:`, error);
            throw error;
        }
    },

    async deleteMaterial(materialId) {
        if (this.mockMode) {
            console.log('Deleting mock material', materialId);
            const index = materials.findIndex(m => m.materialId === materialId);
            if (index === -1) throw new Error('Material not found');
            
            materials.splice(index, 1);
            return { success: true, message: 'Material deleted' };
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/materials/${materialId}/delete`, {
                method: 'POST'
            });

            if (!response.ok) throw new Error('Failed to delete material');
            return await response.json();
        } catch (error) {
            console.error(`Error deleting material ${materialId}:`, error);
            throw error;
        }
    },

    async getAIModels() {
        if (this.mockMode) {
            console.log('Using mock AI models data');
            return [
                { modelId: 1, name: 'GPT-4', category: 'Large Language Model' },
                { modelId: 2, name: 'DALL-E 3', category: 'Image Generation' },
                { modelId: 3, name: 'Claude', category: 'Large Language Model' }
            ];
        }
        
        try {
            const response = await fetch(`${this.baseUrl}/aimodels`);
            if (!response.ok) throw new Error('Failed to fetch AI models');
            return await response.json();
        } catch (error) {
            console.error('Error fetching AI models:', error);
            throw error;
        }
    },
    
    // Switch between mock and real API
    setMockMode(enabled) {
        this.mockMode = enabled;
        console.log(`API is now in ${enabled ? 'mock' : 'real'} mode`);
    }
};


// Excel Export Functions
function exportToExcel(data, filename, sheetName = 'Sheet1') {
    // Ensure SheetJS is available
    if (typeof XLSX === 'undefined') {
        Toast.error('Excel export library not loaded');
        return;
    }

    // Create a worksheet
    const worksheet = XLSX.utils.json_to_sheet(data);

    // Create a workbook
    const workbook = XLSX.utils.book_new();
    XLSX.utils.book_append_sheet(workbook, worksheet, sheetName);

    // Generate and save the Excel file
    XLSX.writeFile(workbook, `${filename}_${new Date().toISOString().split('T')[0]}.xlsx`);
}

// Add export buttons to each panel
function addExportButtons() {
    // Clients Export
    const clientsExportBtn = document.createElement('button');
    clientsExportBtn.innerHTML = '<i class="fas fa-file-excel"></i> Export to Excel';
    clientsExportBtn.className = 'btn btn-secondary ml-2';
    clientsExportBtn.addEventListener('click', () => {
        if (clients.length === 0) {
            Toast.warning('No clients to export');
            return;
        }
        
        // Prepare client data for export
        const exportData = clients.map(client => ({
            'Client ID': client.clientId,
            'First Name': client.firstName,
            'Last Name': client.lastName,
            'Email': client.email,
            'Phone': client.phone,
            'Company': client.company,
            'Position': client.position,
            'AI Models of Interest': client.aiModelsOfInterest ? client.aiModelsOfInterest.join(', ') : '',
            'Sessions Completed': client.sessionsCompleted,
            'Budget': client.budget
        }));
        
        exportToExcel(exportData, 'Clients_List');
    });
    document.getElementById('clients-panel').querySelector('.panel-header').appendChild(clientsExportBtn);

    // Tutors Export
    const tutorsExportBtn = document.createElement('button');
    tutorsExportBtn.innerHTML = '<i class="fas fa-file-excel"></i> Export to Excel';
    tutorsExportBtn.className = 'btn btn-secondary ml-2';
    tutorsExportBtn.addEventListener('click', () => {
        if (tutors.length === 0) {
            Toast.warning('No tutors to export');
            return;
        }
        
        // Prepare tutor data for export
        const exportData = tutors.map(tutor => ({
            'User ID': tutor.userId,
            'First Name': tutor.firstName,
            'Last Name': tutor.lastName,
            'Email': tutor.email,
            'Phone': tutor.phone,
            'AI Specializations': tutor.aiSpecializations ? tutor.aiSpecializations.join(', ') : '',
            'Domain Expertise': tutor.domainExpertise ? tutor.domainExpertise.join(', ') : '',
            'Qualification': tutor.qualification,
            'Experience (Years)': tutor.experienceYears,
            'Hourly Rate': tutor.hourlyRate,
            'Sessions Completed': tutor.sessionsCompleted,
            'Average Rating': tutor.averageRating
        }));
        
        exportToExcel(exportData, 'Tutors_List');
    });
    document.getElementById('tutors-panel').querySelector('.panel-header').appendChild(tutorsExportBtn);

    // Sessions Export
    const sessionsExportBtn = document.createElement('button');
    sessionsExportBtn.innerHTML = '<i class="fas fa-file-excel"></i> Export to Excel';
    sessionsExportBtn.className = 'btn btn-secondary ml-2';
    sessionsExportBtn.addEventListener('click', () => {
        if (sessions.length === 0) {
            Toast.warning('No sessions to export');
            return;
        }
        
        // Prepare session data for export
        const exportData = sessions.map(session => {
            const client = clients.find(c => c.clientId === session.clientId);
            const tutor = tutors.find(t => t.userId === session.tutorId);
            
            return {
                'Session ID': session.sessionId,
                'Client Name': client ? `${client.firstName} ${client.lastName}` : 'Unknown Client',
                'Tutor Name': tutor ? `${tutor.firstName} ${tutor.lastName}` : 'Unknown Tutor',
                'Date': session.sessionDate,
                'Start Time': session.startTime,
                'Duration (Minutes)': session.durationMinutes,
                'Status': session.status,
                'Learning Objectives': session.learningObjectives,
                'Session Cost': session.sessionCost,
                'Is Remote': session.isRemote ? 'Yes' : 'No',
                'Platform': session.platform || 'N/A'
            };
        });
        
        exportToExcel(exportData, 'Tutoring_Sessions');
    });
    document.getElementById('sessions-panel').querySelector('.panel-header').appendChild(sessionsExportBtn);

    // Materials Export
    const materialsExportBtn = document.createElement('button');
    materialsExportBtn.innerHTML = '<i class="fas fa-file-excel"></i> Export to Excel';
    materialsExportBtn.className = 'btn btn-secondary ml-2';
    materialsExportBtn.addEventListener('click', () => {
        if (materials.length === 0) {
            Toast.warning('No materials to export');
            return;
        }
        
        // Prepare materials data for export
        const exportData = materials.map(material => ({
            'Material ID': material.materialId,
            'Title': material.title,
            'Type': material.type,
            'Format': material.format,
            'Author': material.author,
            'Difficulty Level': getDifficultyText(material.difficultyLevel),
            'Estimated Time (Minutes)': material.estimatedTimeMinutes,
            'Rating': material.rating,
            'Usage Count': material.usageCount,
            'Tags': material.tags ? material.tags.join(', ') : '',
            'URL': material.url || '',
            'Local Path': material.localPath || ''
        }));
        
        exportToExcel(exportData, 'Learning_Materials');
    });
    document.getElementById('materials-panel').querySelector('.panel-header').appendChild(materialsExportBtn);
}

// Dashboard Hero Update Function
function updateDashboardHero() {
    // Update hero statistics
    const heroClientsCount = document.getElementById('hero-clients');
    const heroTutorsCount = document.getElementById('hero-tutors');
    const heroAIModelsCount = document.getElementById('hero-ai-models');
    
    if (heroClientsCount) {
        heroClientsCount.textContent = clients ? clients.length : 0;
    }
    
    if (heroTutorsCount) {
        heroTutorsCount.textContent = tutors ? tutors.length : 0;
    }
    
    if (heroAIModelsCount) {
        // Use aiModels if available, otherwise default to 3
        heroAIModelsCount.textContent = aiModels ? aiModels.length : 3;
    }
    
    // Animate the AI network graphic in the hero section
    animateAINetwork();
}

// This is referenced in your code but not defined, so adding it
function updateDashboardStats() {
    // Update dashboard counters
    const totalClientsCountElement = document.getElementById('total-clients-count');
    const totalTutorsCountElement = document.getElementById('total-tutors-count');
    const sessionsThisMonthElement = document.getElementById('sessions-this-month');
    const revenueThisMonthElement = document.getElementById('revenue-this-month');
    
    if (totalClientsCountElement) {
        totalClientsCountElement.textContent = clients ? clients.length : 0;
    }
    
    if (totalTutorsCountElement) {
        totalTutorsCountElement.textContent = tutors ? tutors.length : 0;
    }
    
    // Count sessions and revenue this month
    if (sessionsThisMonthElement && revenueThisMonthElement) {
        const thisMonth = new Date().getMonth() + 1;
        const thisYear = new Date().getFullYear();
        
        let monthSessions = 0;
        let monthRevenue = 0;
        
        if (sessions && sessions.length > 0) {
            sessions.forEach(session => {
                if (session.sessionDate) {
                    const sessionDate = new Date(session.sessionDate);
                    if (sessionDate.getMonth() + 1 === thisMonth && sessionDate.getFullYear() === thisYear) {
                        monthSessions++;
                        monthRevenue += session.sessionCost || 0;
                    }
                }
            });
        }
        
        sessionsThisMonthElement.textContent = monthSessions;
        revenueThisMonthElement.textContent = `$${monthRevenue.toFixed(2)}`;
    }
    
    // Also update the hero section
    updateDashboardHero();
}

// Helper function to calculate session cost (for mock mode)
function calculateSessionCost(sessionData) {
    if (!tutors || !sessionData.tutorId) return 0;
    
    // Find the tutor to get hourly rate
    const tutor = tutors.find(t => t.userId === parseInt(sessionData.tutorId));
    if (!tutor) return 0;
    
    // Calculate cost based on duration and hourly rate
    const hours = sessionData.durationMinutes / 60;
    return Math.round(hours * tutor.hourlyRate);
}


// Function to update session counts for clients and tutors
function updateSessionCounts() {
    // Reset all counts first
    clients.forEach(client => {
        client.sessionsCompleted = 0;
    });
    
    tutors.forEach(tutor => {
        tutor.sessionsCompleted = 0;
    });
    
    // Count completed sessions for each client and tutor
    sessions.forEach(session => {
        if (session.status === 'Completed') {
            // Update client session count
            const client = clients.find(c => c.clientId === session.clientId);
            if (client) {
                client.sessionsCompleted = (client.sessionsCompleted || 0) + 1;
            }
            
            // Update tutor session count
            const tutor = tutors.find(t => t.userId === session.tutorId);
            if (tutor) {
                tutor.sessionsCompleted = (tutor.sessionsCompleted || 0) + 1;
            }
        }
    });
    
    // Update UI if needed
    renderClientsTable();
    renderTutorsTable();
}

 function animateAuraiLetters() {
    const letters = document.querySelectorAll('.aurai-full-name .highlight');
    
    letters.forEach((letter, index) => {
      setTimeout(() => {
        letter.classList.add('animate-pop');
        
        // Remove animation class after animation completes
        setTimeout(() => {
          letter.classList.remove('animate-pop');
        }, 500);
      }, index * 150);
    });
  }
  
  // Add animation keyframes to the document
  function addAnimationStyles() {
    const style = document.createElement('style');
    style.textContent = `
      @keyframes pop {
        0% { transform: scale(1); }
        50% { transform: scale(1.3); }
        100% { transform: scale(1); }
      }
      
      .animate-pop {
        display: inline-block;
        animation: pop 0.5s ease;
      }
      
      @keyframes pulse {
        0% { transform: scale(1); opacity: 0.3; }
        100% { transform: scale(1.05); opacity: 0.5; }
      }
      
      @keyframes float {
        0% { transform: translateY(0); }
        100% { transform: translateY(-5px); }
      }
    `;
    document.head.appendChild(style);
  }
  
  // Animate the AI network graphic
  function animateAINetwork() {
    // Add pulsing effect to circles
    const circles = document.querySelectorAll('.circle');
    circles.forEach((circle, index) => {
      circle.style.animation = `pulse ${2 + index * 0.5}s infinite alternate ease-in-out`;
    });
    
    // Add subtle movement to nodes
    const nodes = document.querySelectorAll('.node');
    nodes.forEach((node, index) => {
      node.style.animation = `float ${3 + index * 0.7}s infinite alternate ease-in-out`;
    });
  }
  
  // Initialize on document ready
  document.addEventListener('DOMContentLoaded', function() {
    // Add animation styles
    addAnimationStyles();
    
    // Initialize dashboard hero if it exists
    if (document.getElementById('dashboard-hero')) {
      updateDashboardHero();
    }
    
    // Make sure clients and tutors are loaded
    if (typeof loadClients === 'function') {
      loadClients();
    }
    
    if (typeof loadTutors === 'function') {
      loadTutors();
    }
    
    if (typeof loadSessions === 'function') {
      loadSessions();
    }
    
    if (typeof loadMaterials === 'function') {
      loadMaterials();
    }
  });
  
  // Enhance existing functions to update the hero section
  // Make sure to call updateDashboardHero when loading data
  const originalLoadClients = window.loadClients;
  window.loadClients = async function() {
    if (typeof originalLoadClients === 'function') {
      await originalLoadClients();
    }
    updateDashboardHero();
  };
  
  const originalLoadTutors = window.loadTutors;
  window.loadTutors = async function() {
    if (typeof originalLoadTutors === 'function') {
      await originalLoadTutors();
    }
    updateDashboardHero();
  };
  
  const originalLoadAIModels = window.loadAIModels;
  window.loadAIModels = async function() {
    if (typeof originalLoadAIModels === 'function') {
      await originalLoadAIModels();
    }
    updateDashboardHero();
  };

// Helper Functions
function formatDate(dateString) {
    const options = { year: 'numeric', month: 'long', day: 'numeric' };
    return new Date(dateString).toLocaleDateString(undefined, options);
}

function calculateEndTime(startTime, durationMinutes) {
    const [hours, minutes] = startTime.split(':').map(Number);
    let totalMinutes = hours * 60 + minutes + durationMinutes;
    const endHours = Math.floor(totalMinutes / 60) % 24;
    const endMinutes = totalMinutes % 60;
    return `${endHours.toString().padStart(2, '0')}:${endMinutes.toString().padStart(2, '0')}`;
}

function getDifficultyText(level) {
    const levels = ['Beginner', 'Easy', 'Intermediate', 'Advanced', 'Expert'];
    return levels[level - 1] || 'Unknown';
}

function formatMinutes(minutes) {
    const hours = Math.floor(minutes / 60);
    const mins = minutes % 60;

    if (hours > 0) {
        return `${hours}h ${mins}m`;
    } else {
        return `${mins} min`;
    }
}

// Toast Notification System
const Toast = {
    show(message, type = 'info') {
        const toastContainer = document.getElementById('toast-container');
        const toast = document.createElement('div');
        toast.className = `toast toast-${type}`;
        toast.innerHTML = `
            <span>${message}</span>
            <button class="close-toast">&times;</button>
        `;
        
        toastContainer.appendChild(toast);
        
        // Trigger reflow to allow transition to work
        toast.getBoundingClientRect();
        
        // Add show class to start animation
        toast.classList.add('show');
        
        // Set auto-dismiss
        const dismissTimeout = setTimeout(() => {
            this.dismiss(toast);
        }, 5000);
        
        // Add click handler for close button
        toast.querySelector('.close-toast').addEventListener('click', () => {
            clearTimeout(dismissTimeout);
            this.dismiss(toast);
        });
    },
    
    dismiss(toast) {
        toast.classList.remove('show');
        
        // Wait for the transition to finish before removing
        setTimeout(() => {
            if (toast.parentNode) {
                toast.parentNode.removeChild(toast);
            }
        }, 300);
    },
    
    success(message) {
        this.show(message, 'success');
    },
    
    error(message) {
        this.show(message, 'error');
    },
    
    info(message) {
        this.show(message, 'info');
    },
    
    warning(message) {
        this.show(message, 'warning');
    }
};

// Tag Input Component
class TagInput {
    constructor(containerElement, initialTags = []) {
        this.container = containerElement;
        this.tagInput = this.container.querySelector('input');
        this.tagsContainer = this.container.querySelector('.tags-container');
        this.tags = [...initialTags];
        
        this.render();
        this.bindEvents();
    }
    
    bindEvents() {
        this.tagInput.addEventListener('keydown', (e) => {
            if (e.key === 'Enter' && this.tagInput.value.trim() !== '') {
                e.preventDefault();
                this.addTag(this.tagInput.value.trim());
                this.tagInput.value = '';
            }
        });
    }
    
    addTag(tag) {
        if (!this.tags.includes(tag)) {
            this.tags.push(tag);
            this.render();
        }
    }
    
    removeTag(tag) {
        this.tags = this.tags.filter(t => t !== tag);
        this.render();
    }
    
    render() {
        this.tagsContainer.innerHTML = '';
        
        this.tags.forEach(tag => {
            const tagElement = document.createElement('div');
            tagElement.className = 'tag';
            tagElement.innerHTML = `
                <span>${tag}</span>
                <i class="fas fa-times"></i>
            `;
            
            tagElement.querySelector('i').addEventListener('click', () => {
                this.removeTag(tag);
            });
            
            this.tagsContainer.appendChild(tagElement);
        });
    }
    
    getTags() {
        return [...this.tags];
    }
    
    setTags(tags) {
        this.tags = [...tags];
        this.render();
    }
}

// App State Management
let clients = [];
let tutors = [];
let sessions = [];
let materials = [];
let aiModels = [];

// DOM References - Navigation
const navItems = document.querySelectorAll('.sidebar li');
const panels = document.querySelectorAll('.panel');

// DOM References - Clients
const clientsLoading = document.getElementById('clients-loading');
const clientsList = document.getElementById('clients-list');
const clientsMessage = document.getElementById('clients-message');
const addClientBtn = document.getElementById('add-client-btn');
const clientForm = document.getElementById('client-form');
const clientFormTitle = document.getElementById('client-form-title');
const saveClientBtn = document.getElementById('save-client-btn');
const cancelClientBtn = document.getElementById('cancel-client-btn');
const closeClientFormBtn = document.getElementById('close-client-form');
const clientSearchInput = document.getElementById('client-search-input');
const clientSearchType = document.getElementById('client-search-type');
const clientSearchBtn = document.getElementById('client-search-btn');
const clearClientSearchBtn = document.getElementById('clear-client-search');

// DOM References - Tutors
const tutorsLoading = document.getElementById('tutors-loading');
const tutorsList = document.getElementById('tutors-list');
const tutorsMessage = document.getElementById('tutors-message');
const addTutorBtn = document.getElementById('add-tutor-btn');
const tutorForm = document.getElementById('tutor-form');
const tutorFormTitle = document.getElementById('tutor-form-title');
const saveTutorBtn = document.getElementById('save-tutor-btn');
const cancelTutorBtn = document.getElementById('cancel-tutor-btn');
const closeTutorFormBtn = document.getElementById('close-tutor-form');
const tutorSearchInput = document.getElementById('tutor-search-input');
const tutorSearchType = document.getElementById('tutor-search-type');
const tutorSearchBtn = document.getElementById('tutor-search-btn');
const clearTutorSearchBtn = document.getElementById('clear-tutor-search');


// DOM References - Sessions
const sessionsLoading = document.getElementById('sessions-loading');
const sessionsList = document.getElementById('sessions-list');
const sessionsMessage = document.getElementById('sessions-message');
const addSessionBtn = document.getElementById('add-session-btn');
const sessionForm = document.getElementById('session-form');
const sessionFormTitle = document.getElementById('session-form-title');
const saveSessionBtn = document.getElementById('save-session-btn');
const cancelSessionBtn = document.getElementById('cancel-session-btn');
const closeSessionFormBtn = document.getElementById('close-session-form');
const sessionTypeRadios = document.querySelectorAll('input[name="sessionType"]');
const platformGroup = document.getElementById('platformGroup');

// DOM References - Materials
const materialsLoading = document.getElementById('materials-loading');
const materialsList = document.getElementById('materials-list');
const materialsMessage = document.getElementById('materials-message');
const addMaterialBtn = document.getElementById('add-material-btn');
const materialForm = document.getElementById('material-form');
const materialFormTitle = document.getElementById('material-form-title');
const saveMaterialBtn = document.getElementById('save-material-btn');
const cancelMaterialBtn = document.getElementById('cancel-material-btn');
const closeMaterialFormBtn = document.getElementById('close-material-form');

// DOM References - Dashboard
const totalClientsCount = document.getElementById('total-clients-count');
const totalTutorsCount = document.getElementById('total-tutors-count');
const sessionsThisMonth = document.getElementById('sessions-this-month');
const revenueThisMonth = document.getElementById('revenue-this-month');
const dashboardSessionsList = document.getElementById('dashboard-sessions-list');
const popularMaterialsList = document.getElementById('popular-materials-list');

// Tag Input Instances
let clientAIModelsInput;
let tutorSpecializationsInput;
let tutorExpertiseInput;
let materialTagsInput;

// Current editing IDs
let currentEditingClientId = null;
let currentEditingTutorId = null;
let currentEditingSessionId = null;
let currentEditingMaterialId = null;

// Navigation Event Handlers
navItems.forEach(item => {
    item.addEventListener('click', () => {
        // Update active navigation item
        navItems.forEach(i => i.classList.remove('active'));
        item.classList.add('active');
        
        // Show corresponding panel
        const panelId = item.dataset.panel;
        panels.forEach(panel => {
            panel.classList.remove('active');
            if (panel.id === panelId) {
                panel.classList.add('active');
                
                // Load data when panel becomes active if it hasn't been loaded yet
                if (panelId === 'tutors-panel' && !tutorsList.innerHTML) {
                    loadTutors();
                } else if (panelId === 'clients-panel' && !clientsList.innerHTML) {
                    loadClients();
                } else if (panelId === 'sessions-panel' && !sessionsList.innerHTML) {
                    loadSessions();
                } else if (panelId === 'materials-panel' && !materialsList.innerHTML) {
                    loadMaterials();
                } else if (panelId === 'dashboard-panel') {
                    updateDashboard();
                }
            }
        });
    });
});

// Initialize search event listeners
function initializeSearchFunctionality() {
    // Client search event listeners
    if (clientSearchBtn) {
        clientSearchBtn.addEventListener('click', searchClients);
        clientSearchBtn.hasListener = true;
    }
    
    if (clientSearchInput) {
        clientSearchInput.addEventListener('keypress', function(e) {
            if (e.key === 'Enter') {
                searchClients();
            }
        });
        clientSearchInput.hasListener = true;
    }
    
    if (clearClientSearchBtn) {
        clearClientSearchBtn.addEventListener('click', clearClientSearch);
        clearClientSearchBtn.hasListener = true;
    }
    
    // Tutor search event listeners
    if (tutorSearchBtn) {
        tutorSearchBtn.addEventListener('click', searchTutors);
        tutorSearchBtn.hasListener = true;
    }
    
    if (tutorSearchInput) {
        tutorSearchInput.addEventListener('keypress', function(e) {
            if (e.key === 'Enter') {
                searchTutors();
            }
        });
        tutorSearchInput.hasListener = true;
    }
    
    if (clearTutorSearchBtn) {
        clearTutorSearchBtn.addEventListener('click', clearTutorSearch);
        clearTutorSearchBtn.hasListener = true;
    }
    
    // Add highlight styles
    addHighlightStyles();
}

// Function to highlight search matches in text
function highlightText(text, searchTerm) {
    if (!searchTerm || searchTerm === '') return text;
    
    // Escape special regex characters in the search term
    const escapedSearchTerm = searchTerm.replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
    const regex = new RegExp(`(${escapedSearchTerm})`, 'gi');
    
    return text.replace(regex, '<span class="highlight">$1</span>');
}

// Add CSS for highlighted text
function addHighlightStyles() {
    // Check if highlight styles already exist
    if (!document.getElementById('search-highlight-styles')) {
        const style = document.createElement('style');
        style.id = 'search-highlight-styles';
        style.textContent = `
            .highlight {
                background-color: rgba(37, 99, 235, 0.2);
                padding: 2px 0;
                border-radius: 2px;
                font-weight: bold;
                color: var(--primary-dark);
            }
        `;
        document.head.appendChild(style);
    }
}

function searchClients() {
    const searchText = clientSearchInput.value.trim().toLowerCase();
    const searchType = clientSearchType.value;
    
    // If search text is empty, show all clients
    if (searchText === '') {
        renderClientsTable();
        return;
    }
    
    // Filter clients based on search criteria
    const filteredClients = clients.filter(client => {
        switch (searchType) {
            case 'name':
                const fullName = `${client.firstName} ${client.lastName}`.toLowerCase();
                return fullName.includes(searchText);
            
            case 'email':
                return client.email.toLowerCase().includes(searchText);
            
            case 'company':
                return client.company && client.company.toLowerCase().includes(searchText);
            
            default:
                return true;
        }
    });
    
    // Show message if no results found
    if (filteredClients.length === 0) {
        showMessage(clientsMessage, `No clients found matching "${searchText}" in ${searchType}`, 'info');
        clientsList.innerHTML = '';
        return;
    }
    
    // Render filtered clients with highlighting
    renderFilteredClients(filteredClients, searchText, searchType);
    
    // Show success message
    showMessage(clientsMessage, `Found ${filteredClients.length} client(s) matching "${searchText}" in ${searchType}`, 'success');
}

// Render filtered clients with highlighting
function renderFilteredClients(filteredClients, searchText, searchType) {
    clientsList.innerHTML = '';
    
    filteredClients.forEach(client => {
        // Create base content
        let nameContent = `${client.firstName} ${client.lastName}`;
        let emailContent = client.email;
        let companyContent = client.company || 'N/A';
        
        // Apply highlighting based on search type
        if (searchText && searchText !== '') {
            if (searchType === 'name') {
                nameContent = highlightText(nameContent, searchText);
            } else if (searchType === 'email') {
                emailContent = highlightText(emailContent, searchText);
            } else if (searchType === 'company') {
                companyContent = highlightText(companyContent, searchText);
            }
        }
        
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${nameContent}</td>
            <td>${emailContent}</td>
            <td>${companyContent}</td>
            <td>${client.sessionsCompleted || 0}</td>
            <td>$${client.budget || 0}</td>
            <td class="action-icons">
                <i class="fas fa-edit action-icon" data-id="${client.clientId}"></i>
                <i class="fas fa-trash action-icon delete" data-id="${client.clientId}"></i>
            </td>
        `;
        clientsList.appendChild(row);
    });
    
    // Add event listeners for edit/delete icons
    clientsList.querySelectorAll('.fa-edit').forEach(icon => {
        icon.addEventListener('click', () => {
            const clientId = parseInt(icon.dataset.id);
            editClient(clientId);
        });
    });
    
    clientsList.querySelectorAll('.fa-trash').forEach(icon => {
        icon.addEventListener('click', () => {
            const clientId = parseInt(icon.dataset.id);
            if (confirm('Are you sure you want to delete this client?')) {
                deleteClient(clientId);
            }
        });
    });
}

// Clear client search
function clearClientSearch() {
    if (clientSearchInput) {
        clientSearchInput.value = '';
    }
    renderClientsTable();
    if (clientsMessage) {
        clientsMessage.style.display = 'none';
    }
}

// ===================== TUTOR SEARCH =====================
function renderTutorsTable() {
    tutorsList.innerHTML = '';
    
    if (!tutors || tutors.length === 0) {
        showMessage(tutorsMessage, 'No tutors found', 'info');
        return;
    }
    
    tutors.forEach(tutor => {
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${tutor.firstName} ${tutor.lastName}</td>
            <td>${tutor.email}</td>
            <td>${tutor.phone || 'N/A'}</td>
            <td>${tutor.aiSpecializations ? tutor.aiSpecializations.join(', ') : 'None'}</td>
            <td>${tutor.domainExpertise ?tutor.domainExpertise .join(', '): 'None'} </td>
            <td>${tutor.experienceYears || 0} years</td>
            <td>$${tutor.hourlyRate || 0}/hour</td>
            <td class="action-icons">
                <i class="fas fa-edit action-icon" data-id="${tutor.userId}"></i>
                <i class="fas fa-trash action-icon delete" data-id="${tutor.userId}"></i>
            </td>
        `;
        tutorsList.appendChild(row);
    });
    
    // Add event listeners for edit/delete icons
    tutorsList.querySelectorAll('.fa-edit').forEach(icon => {
        icon.addEventListener('click', () => {
            const tutorId = parseInt(icon.dataset.id);
            editTutor(tutorId);
        });
    });
    
    tutorsList.querySelectorAll('.fa-trash').forEach(icon => {
        icon.addEventListener('click', () => {
            const tutorId = parseInt(icon.dataset.id);
            if (confirm('Are you sure you want to delete this tutor?')) {
                deleteTutor(tutorId);
            }
        });
    });
}

// Tutor search functionality
function searchTutors() {
    const searchText = tutorSearchInput.value.trim().toLowerCase();
    const searchType = tutorSearchType.value;
    
    // If search text is empty, show all tutors
    if (searchText === '') {
        renderTutorsTable();
        return;
    }
    
    // Filter tutors based on search criteria
    const filteredTutors = tutors.filter(tutor => {
        switch (searchType) {
            case 'name':
                const fullName = `${tutor.firstName} ${tutor.lastName}`.toLowerCase();
                return fullName.includes(searchText);
            
            case 'email':
                return tutor.email.toLowerCase().includes(searchText);
            
            case 'specialization':
                // Check if any specialization includes the search text
                return tutor.aiSpecializations && 
                       tutor.aiSpecializations.some(spec => spec.toLowerCase().includes(searchText));
            
            case 'expertise':
                // Check if any domain expertise includes the search text
                return tutor.domainExpertise && 
                       tutor.domainExpertise.some(domain => domain.toLowerCase().includes(searchText));
            
            default:
                return true;
        }
    });
    
    // Show message if no results found
    if (filteredTutors.length === 0) {
        showMessage(tutorsMessage, `No tutors found matching "${searchText}" in ${searchType}`, 'info');
        tutorsList.innerHTML = '';
        return;
    }
    
    // Render filtered tutors with highlighting
    renderFilteredTutors(filteredTutors, searchText, searchType);
    
    // Show success message
    showMessage(tutorsMessage, `Found ${filteredTutors.length} tutor(s) matching "${searchText}" in ${searchType}`, 'success');
}

// Render filtered tutors with highlighting
function renderFilteredTutors(filteredTutors, searchText, searchType) {
    tutorsList.innerHTML = '';
    
    filteredTutors.forEach(tutor => {
        // Create base content
        let nameContent = `${tutor.firstName} ${tutor.lastName}`;
        let emailContent = tutor.email;
        let phoneContent = tutor.phone || 'N/A';
        let specializationsContent = tutor.aiSpecializations ? tutor.aiSpecializations.join(', ') : 'None';
        let expertiseContent = tutor.domainExpertise ? tutor.domainExpertise.join(', ') : 'None';
        
        // Apply highlighting based on search type
        if (searchText && searchText !== '') {
            if (searchType === 'name') {
                nameContent = highlightText(nameContent, searchText);
            } else if (searchType === 'email') {
                emailContent = highlightText(emailContent, searchText);
            } else if (searchType === 'specialization') {
                specializationsContent = highlightText(specializationsContent, searchText);
            } else if (searchType === 'expertise') {
                expertiseContent = highlightText(expertiseContent, searchText);
            }
        }
        
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${nameContent}</td>
            <td>${emailContent}</td>
            <td>${phoneContent}</td>
            <td>${specializationsContent}</td>
            <td>${tutor.experienceYears} years</td>
            <td>$${tutor.hourlyRate}/hour</td>
            <td class="action-icons">
                <i class="fas fa-edit action-icon" data-id="${tutor.userId}"></i>
                <i class="fas fa-trash action-icon delete" data-id="${tutor.userId}"></i>
            </td>
        `;
        tutorsList.appendChild(row);
    });
    
    // Add event listeners for edit/delete icons
    tutorsList.querySelectorAll('.fa-edit').forEach(icon => {
        icon.addEventListener('click', () => {
            const tutorId = parseInt(icon.dataset.id);
            editTutor(tutorId);
        });
    });
    
    tutorsList.querySelectorAll('.fa-trash').forEach(icon => {
        icon.addEventListener('click', () => {
            const tutorId = parseInt(icon.dataset.id);
            if (confirm('Are you sure you want to delete this tutor?')) {
                deleteTutor(tutorId);
            }
        });
    });
}

// Clear tutor search
function clearTutorSearch() {
    if (tutorSearchInput) {
        tutorSearchInput.value = '';
    }
    renderTutorsTable();
    if (tutorsMessage) {
        tutorsMessage.style.display = 'none';
    }
}

// Load Clients
async function loadClients() {
    clientsList.innerHTML = '';
    clientsLoading.style.display = 'block';
    clientsMessage.style.display = 'none';

    try {
        clients = await apiService.getClients();

        if (clients.length === 0) {
            showMessage(clientsMessage, 'No clients found', 'info');
        } else {
            // Update session counts before rendering
            updateSessionCounts();
            renderClientsTable();
        }
        
        clients = await apiService.getClients();

        if (clients.length === 0) {
            showMessage(clientsMessage, 'No clients found', 'info');
        } else {
            renderClientsTable();
        }
        
        // Ensure client search elements are properly referenced
        const clientSearchInput = document.getElementById('client-search-input');
        const clientSearchType = document.getElementById('client-search-type');
        const clientSearchBtn = document.getElementById('client-search-btn');
        const clearClientSearchBtn = document.getElementById('clear-client-search');
        
        if (clientSearchBtn && !clientSearchBtn.hasListener) {
            clientSearchBtn.addEventListener('click', searchClients);
            clientSearchBtn.hasListener = true;
        }
        
        if (clientSearchInput && !clientSearchInput.hasListener) {
            clientSearchInput.addEventListener('keypress', function(e) {
                if (e.key === 'Enter') {
                    searchClients();
                }
            });
            clientSearchInput.hasListener = true;
        }
        
        if (clearClientSearchBtn && !clearClientSearchBtn.hasListener) {
            clearClientSearchBtn.addEventListener('click', clearClientSearch);
            clearClientSearchBtn.hasListener = true;
        }
        
        // Update client select in session form
        updateClientSelect();
        
        // Update dashboard if needed
        updateDashboardStats();
    } catch (error) {
        console.error('Error loading clients:', error);
        showMessage(clientsMessage, 'Error loading clients: ' + error.message, 'error');
        
        // Fallback to mock data
        mockClients();
    } finally {
        clientsLoading.style.display = 'none';
    }
}


// Function to mark a session as completed and increment client session count
function completeSession(sessionId) {
    const session = sessions.find(s => s.sessionId === parseInt(sessionId));
    if (!session) {
        Toast.error('Session not found');
        return;
    }
    
    const oldStatus = session.status;
    
    // Update session status
    session.status = 'Completed';
    
    // Optional: You could show a dialog to collect rating
    const rating = 5; // Default rating or get from user input
    
    // Update session in the database/API
    apiService.updateSession(sessionId, {
        status: 'Completed',
        clientRating: rating
    }).then(() => {
        Toast.success('Session marked as completed');
        
        // Only update session counts if the status actually changed
        if (oldStatus !== 'Completed') {
            updateSessionCounts();
        }
        
        // Refresh sessions table
        renderSessionsTable();
        updateDashboardSessions();
    }).catch(error => {
        console.error('Error completing session:', error);
        Toast.error('Failed to complete session: ' + error.message);
        
        // Revert status change on error
        session.status = oldStatus;
    });
}

function updateSessionCounts() {
    console.log("Updating session counts...");
    
    // Reset all counts first
    clients.forEach(client => {
        client.sessionsCompleted = 0;
    });
    
    tutors.forEach(tutor => {
        tutor.sessionsCompleted = 0;
    });
    
    // Count completed sessions for each client and tutor
    sessions.forEach(session => {
        if (session.status === 'Completed') {
            // Update client session count
            const client = clients.find(c => c.clientId === session.clientId);
            if (client) {
                client.sessionsCompleted = (client.sessionsCompleted || 0) + 1;
            }
            
            // Update tutor session count
            const tutor = tutors.find(t => t.userId === session.tutorId);
            if (tutor) {
                tutor.sessionsCompleted = (tutor.sessionsCompleted || 0) + 1;
            }
        }
    });
    
    console.log("Session counts updated.");
    
    // Update UI if needed
    if (clientsList && clientsList.innerHTML) {
        renderClientsTable();
    }
    if (tutorsList && tutorsList.innerHTML) {
        renderTutorsTable();
    }
    
    // Update dashboard stats if visible
    if (document.getElementById('dashboard-panel').classList.contains('active')) {
        updateDashboardStats();
    }
}

// Add the missing incrementTutorSessions helper function
function incrementTutorSessions(tutorId) {
    const tutor = tutors.find(t => t.userId === tutorId);
    if (!tutor) {
        console.error(`Tutor with ID ${tutorId} not found.`);
        return false;
    }
    
    // Update tutor's sessions count
    tutor.sessionsCompleted = (tutor.sessionsCompleted || 0) + 1;
    
    // No need to make an API call here since updateSessionCounts will handle this
    
    return true;
}


// Function to increment a client's completed sessions
async function incrementClientSessions(clientId, sessionDate) {
    try {
        // Find the client in the local array
        const client = clients.find(c => c.clientId === clientId);
        if (!client) {
            console.error(`Client with ID ${clientId} not found.`);
            return false;
        }
        
        // Update client's sessions count and last session date
        client.sessionsCompleted = (client.sessionsCompleted || 0) + 1;
        client.lastSessionDate = sessionDate;
        
        // Update the client through API
        await apiService.updateClient(clientId, {
            sessionsCompleted: client.sessionsCompleted,
            lastSessionDate: sessionDate
        });
        
        // Reload clients to refresh UI
        await loadClients();
        
        Toast.success(`Session recorded for ${client.firstName} ${client.lastName}`);
        return true;
    } catch (error) {
        console.error('Error incrementing client sessions:', error);
        Toast.error('Failed to update client session count');
        return false;
    }
}

function renderSessionsTable() {
    sessionsList.innerHTML = '';
    
    sessions.forEach(session => {
        const client = clients.find(c => c.clientId === session.clientId);
        const tutor = tutors.find(t => t.userId === session.tutorId);
        
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${client ? client.firstName + ' ' + client.lastName : 'Unknown Client'}</td>
            <td>${tutor ? tutor.firstName + ' ' + tutor.lastName : 'Unknown Tutor'}</td>
            <td>${formatDate(session.sessionDate)}</td>
            <td>${session.startTime} - ${calculateEndTime(session.startTime, session.durationMinutes)}</td>
            <td><span class="status ${session.status.toLowerCase()}">${session.status}</span></td>
            <td class="action-icons">
                ${session.status === 'Scheduled' ? 
                  '<i class="fas fa-check-circle action-icon complete-btn" title="Mark as Completed" data-id="' + session.sessionId + '"></i>' : ''}
                <i class="fas fa-edit action-icon" data-id="${session.sessionId}"></i>
                <i class="fas fa-trash action-icon delete" data-id="${session.sessionId}"></i>
            </td>
        `;
        sessionsList.appendChild(row);
    });
    
    // Add event listeners for edit/delete icons
    sessionsList.querySelectorAll('.fa-edit').forEach(icon => {
        icon.addEventListener('click', () => {
            const sessionId = parseInt(icon.dataset.id);
            editSession(sessionId);
        });
    });
    
    sessionsList.querySelectorAll('.fa-trash').forEach(icon => {
        icon.addEventListener('click', () => {
            const sessionId = parseInt(icon.dataset.id);
            if (confirm('Are you sure you want to cancel this session?')) {
                cancelSession(sessionId);
            }
        });
    });
    
    // Add event listeners for complete button
    sessionsList.querySelectorAll('.complete-btn').forEach(icon => {
        icon.addEventListener('click', () => {
            const sessionId = parseInt(icon.dataset.id);
            if (confirm('Mark this session as completed?')) {
                completeSession(sessionId);
            }
        });
    });
}

// Function to mark a session as completed and update client's session count
function completeSession(sessionId) {
    const session = sessions.find(s => s.sessionId === sessionId);
    if (!session) {
        Toast.error('Session not found');
        return;
    }
    
    // Update session status
    session.status = 'Completed';
    
    // Optional: You could show a dialog to collect rating
    const rating = 5; // Default rating or get from user input
    
    // Update session in the database/API
    apiService.updateSession(sessionId, {
        status: 'Completed',
        clientRating: rating
    }).then(() => {
        // After session is marked as completed, increment client sessions
        incrementClientSessions(session.clientId, session.sessionDate);
        
        // Also update the tutor's completed sessions if needed
        if (session.tutorId) {
            incrementTutorSessions(session.tutorId);
        }
        
        // Refresh sessions table
        renderSessionsTable();
        updateDashboardSessions();
    }).catch(error => {
        console.error('Error completing session:', error);
        Toast.error('Failed to complete session');
    });
}

// Render clients table
function renderClientsTable() {
    clientsList.innerHTML = '';
    
    clients.forEach(client => {

        let aiModelsOfInterest = formatSpecialization(client.aiModelsOfInterest || client.aiModelsOfInterest);

        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${client.firstName} ${client.lastName}</td>
            <td>${client.email}</td>
            <td>${client.company || 'N/A'}</td>
            <td>${client.aiModelsOfInterest}</td>
            <td>${client.sessionsCompleted || 0}</td>
            <td>$${client.budget || 0}</td>
            <td class="action-icons">
                <i class="fas fa-edit action-icon" data-id="${client.clientId}"></i>
                <i class="fas fa-trash action-icon delete" data-id="${client.clientId}"></i>
            </td>
        `;
        clientsList.appendChild(row);
    });
    
    // Add event listeners for edit/delete icons
    clientsList.querySelectorAll('.fa-edit').forEach(icon => {
        icon.addEventListener('click', () => {
            const clientId = parseInt(icon.dataset.id);
            editClient(clientId);
        });
    });
    
    clientsList.querySelectorAll('.fa-trash').forEach(icon => {
        icon.addEventListener('click', () => {
            const clientId = parseInt(icon.dataset.id);
            if (confirm('Are you sure you want to delete this client?')) {
                deleteClient(clientId);
            }
        });
    });
}

// Client Form Handlers
addClientBtn.addEventListener('click', () => {
    showClientForm();
});

closeClientFormBtn.addEventListener('click', () => {
    hideClientForm();
});

cancelClientBtn.addEventListener('click', () => {
    hideClientForm();
});

// In webui/app.js, update the saveClientBtn click handler

saveClientBtn.addEventListener('click', async () => {
    const firstName = document.getElementById('firstName').value;
    const lastName = document.getElementById('lastName').value;
    const email = document.getElementById('email').value;
    
    if (!firstName || !lastName || !email) {
        Toast.error('Please fill in all required fields');
        return;
    }
    
    const clientData = {
        firstName: firstName,
        lastName: lastName,
        email: email,
        phone: document.getElementById('phone').value,
        company: document.getElementById('company').value,
        position: document.getElementById('position').value,
        budget: parseFloat(document.getElementById('budget').value) || 0,
        aiModelsOfInterest: clientAIModelsInput ? clientAIModelsInput.getTags() : [],
        registrationDate: new Date().toISOString().split('T')[0],
        sessionsCompleted: 0
    };
    
    try {
        let result;
        if (currentEditingClientId) {
            // Update existing client
            result = await apiService.updateClient(currentEditingClientId, clientData);
            Toast.success('Client updated successfully');
        } else {
            // Add new client
            result = await apiService.addClient(clientData);
            Toast.success('Client added successfully');
            console.log('Add client result:', result); // Debug logging
        }
        
        // Hide form
        hideClientForm();
        
        // Explicitly reload clients to refresh the table
        await loadClients();
    } catch (error) {
        Toast.error('Error: ' + error.message);
        console.error('Error saving client:', error);
        
        // Fallback for demo/testing
        if (!currentEditingClientId) {
            // Add client to local array for demo purposes
            const newId = clients.length > 0 ? Math.max(...clients.map(c => c.clientId)) + 1 : 1;
            clientData.clientId = newId;
            clients.push(clientData);
            renderClientsTable();
            Toast.warning('Using local mode: Client added to temporary storage');
        }
    }
});

// Show client form for adding or editing
function showClientForm(client = null) {
    // Reset form
    document.getElementById('firstName').value = '';
    document.getElementById('lastName').value = '';
    document.getElementById('email').value = '';
    document.getElementById('phone').value = '';
    document.getElementById('company').value = '';
    document.getElementById('position').value = '';
    document.getElementById('budget').value = '';
    
    // Initialize tag input if needed
    if (!clientAIModelsInput) {
        clientAIModelsInput = new TagInput(document.getElementById('clientAIModels'));
    } else {
        clientAIModelsInput.setTags([]);
    }
    
    // Set form mode
    if (client) {
        clientFormTitle.textContent = 'Edit Client';
        currentEditingClientId = client.clientId;
        
        // Fill form with client data
        document.getElementById('firstName').value = client.firstName;
        document.getElementById('lastName').value = client.lastName;
        document.getElementById('email').value = client.email;
        document.getElementById('phone').value = client.phone || '';
        document.getElementById('company').value = client.company || '';
        document.getElementById('position').value = client.position || '';
        document.getElementById('budget').value = client.budget || '';
        
        // Set AI models
        if (client.aiModelsOfInterest && client.aiModelsOfInterest.length > 0) {
            clientAIModelsInput.setTags(client.aiModelsOfInterest);
        }
    } else {
        clientFormTitle.textContent = 'Add New Client';
        currentEditingClientId = null;
    }
    
    // Show form
    clientForm.style.display = 'block';
    addClientBtn.style.display = 'none';
}

// Hide client form
function hideClientForm() {
    clientForm.style.display = 'none';
    addClientBtn.style.display = 'block';
    currentEditingClientId = null;
}

// Edit client
async function editClient(clientId) {
    try {
        const client = clients.find(c => c.clientId === clientId);
        if (client) {
            showClientForm(client);
        } else {
            // If client not found in local array, try to fetch it
            const fetchedClient = await apiService.getClientById(clientId);
            showClientForm(fetchedClient);
        }
    } catch (error) {
        Toast.error('Error fetching client details: ' + error.message);
        console.error('Error fetching client details:', error);
    }
}

// Delete client
async function deleteClient(clientId) {
    try {
        await apiService.deleteClient(clientId);
        Toast.success('Client deleted successfully');
        
        // Remove from local array and update UI
        clients = clients.filter(c => c.clientId !== clientId);
        renderClientsTable();
        
        // Update client select in session form
        updateClientSelect();
        
        // Update dashboard
        updateDashboardStats();
    } catch (error) {
        Toast.error('Error deleting client: ' + error.message);
        console.error('Error deleting client:', error);
    }
}

async function loadTutors() {
    tutorsList.innerHTML = '';
    tutorsLoading.style.display = 'block';
    tutorsMessage.style.display = 'none';

    try {
        tutors = await apiService.getTutors();

        if (tutors.length === 0) {
            showMessage(tutorsMessage, 'No tutors found', 'info');
        } else {
            renderTutorsTable();
        }
        
        // Ensure tutor search elements are properly referenced
        const tutorSearchInput = document.getElementById('tutor-search-input');
        const tutorSearchType = document.getElementById('tutor-search-type');
        const tutorSearchBtn = document.getElementById('tutor-search-btn');
        const clearTutorSearchBtn = document.getElementById('clear-tutor-search');
        
        if (tutorSearchBtn && !tutorSearchBtn.hasListener) {
            tutorSearchBtn.addEventListener('click', searchTutors);
            tutorSearchBtn.hasListener = true;
        }
        
        if (tutorSearchInput && !tutorSearchInput.hasListener) {
            tutorSearchInput.addEventListener('keypress', function(e) {
                if (e.key === 'Enter') {
                    searchTutors();
                }
            });
            tutorSearchInput.hasListener = true;
        }
        
        if (clearTutorSearchBtn && !clearTutorSearchBtn.hasListener) {
            clearTutorSearchBtn.addEventListener('click', clearTutorSearch);
            clearTutorSearchBtn.hasListener = true;
        }
        
        // Update tutor select in session form
        updateTutorSelect();
        
        // Update dashboard if needed
        updateDashboardStats();
    } catch (error) {
        console.error('Error loading tutors:', error);
        showMessage(tutorsMessage, 'Error loading tutors: ' + error.message, 'error');
        
        // Fallback to mock data
        mockTutors();
    } finally {
        tutorsLoading.style.display = 'none';
    }
}

// Add event listeners for tutor search
tutorSearchBtn.addEventListener('click', searchTutors);
tutorSearchInput.addEventListener('keypress', function(e) {
    if (e.key === 'Enter') {
        searchTutors();
    }
});

// Tutor search function
function searchTutors() {
    const searchText = tutorSearchInput.value.trim().toLowerCase();
    const searchType = tutorSearchType.value;
    
    // If search text is empty, show all tutors
    if (searchText === '') {
        renderTutorsTable();
        return;
    }
    
    // Filter tutors based on search criteria
    const filteredTutors = tutors.filter(tutor => {
        switch (searchType) {
            case 'name':
                const fullName = `${tutor.firstName} ${tutor.lastName}`.toLowerCase();
                return fullName.includes(searchText);
            
            case 'email':
                return tutor.email.toLowerCase().includes(searchText);
            
            case 'specialization':
                // Check if any specialization includes the search text
                return tutor.aiSpecializations && 
                       tutor.aiSpecializations.some(spec => spec.toLowerCase().includes(searchText));
            
            case 'expertise':
                // Check if any domain expertise includes the search text
                return tutor.domainExpertise && 
                       tutor.domainExpertise.some(domain => domain.toLowerCase().includes(searchText));
            
            default:
                return true;
        }
    });
    
    // Show message if no results found
    if (filteredTutors.length === 0) {
        showMessage(tutorsMessage, `No tutors found matching "${searchText}" in ${searchType}`, 'info');
        tutorsList.innerHTML = '';
        return;
    }
    
    // Render filtered tutors
    renderFilteredTutors(filteredTutors);
    
    // Show success message
    showMessage(tutorsMessage, `Found ${filteredTutors.length} tutor(s) matching "${searchText}" in ${searchType}`, 'success');
}


function formatSpecialization(data) {
    if (!data) return 'None';
    
    // If it's already a string, return it
    if (typeof data === 'string') {
        return data.trim() || 'None';
    }
    
    // If it's an array, join it
    if (Array.isArray(data)) {
        return data.length > 0 ? data.join(', ') : 'None';
    }
    
    // If it's an object, try to handle it
    if (typeof data === 'object') {
        try {
            const arr = Object.values(data);
            return arr.length > 0 ? arr.join(', ') : 'None';
        } catch (e) {
            return 'None';
        }
    }
    
    return 'None';
}

// Tutor Form Handlers
addTutorBtn.addEventListener('click', () => {
    showTutorForm();
});

closeTutorFormBtn.addEventListener('click', () => {
    hideTutorForm();
});

cancelTutorBtn.addEventListener('click', () => {
    hideTutorForm();
});

saveTutorBtn.addEventListener('click', async () => {
    const firstName = document.getElementById('tutorFirstName').value;
    const lastName = document.getElementById('tutorLastName').value;
    const email = document.getElementById('tutorEmail').value;
    const qualification = document.getElementById('tutorQualification').value;
    
    if (!firstName || !lastName || !email || !qualification) {
        Toast.error('Please fill in all required fields');
        return;
    }
    
    const tutorData = {
        firstName: firstName,
        lastName: lastName,
        email: email,
        phone: document.getElementById('tutorPhone').value,
        qualification: qualification,
        experienceYears: parseInt(document.getElementById('tutorExperienceYears').value) || 0,
        hourlyRate: parseFloat(document.getElementById('tutorHourlyRate').value) || 0,
        username: document.getElementById('tutorUsername').value || email.split('@')[0],
        aiSpecializations: tutorSpecializationsInput ? tutorSpecializationsInput.getTags() : [],
        domainExpertise: tutorExpertiseInput ? tutorExpertiseInput.getTags() : []
    };
    
    // Add password only if provided (for security)
    const password = document.getElementById('tutorPassword').value;
    if (password) {
        tutorData.password = password;
    }
    
    try {
        if (currentEditingTutorId) {
            // Update existing tutor
            await apiService.updateTutor(currentEditingTutorId, tutorData);
            Toast.success('Tutor updated successfully');
        } else {
            // Add new tutor
            await apiService.addTutor(tutorData);
            Toast.success('Tutor added successfully');
        }
        
        // Hide form and reload tutors
        hideTutorForm();
        loadTutors();
    } catch (error) {
        Toast.error('Error: ' + error.message);
        console.error('Error saving tutor:', error);
    }
});

// Show tutor form for adding or editing
function showTutorForm(tutor = null) {
    // Reset form
    document.getElementById('tutorFirstName').value = '';
    document.getElementById('tutorLastName').value = '';
    document.getElementById('tutorEmail').value = '';
    document.getElementById('tutorPhone').value = '';
    document.getElementById('tutorQualification').value = '';
    document.getElementById('tutorExperienceYears').value = '';
    document.getElementById('tutorHourlyRate').value = '';
    document.getElementById('tutorUsername').value = '';
    document.getElementById('tutorPassword').value = '';
    
    // Initialize tag inputs if needed
    if (!tutorSpecializationsInput) {
        tutorSpecializationsInput = new TagInput(document.getElementById('tutorSpecializations'));
    } else {
        tutorSpecializationsInput.setTags([]);
    }
    
    if (!tutorExpertiseInput) {
        tutorExpertiseInput = new TagInput(document.getElementById('tutorExpertise'));
    } else {
        tutorExpertiseInput.setTags([]);
    }
    
    // Set form mode
    if (tutor) {
        tutorFormTitle.textContent = 'Edit Tutor';
        currentEditingTutorId = tutor.userId;
        
        // Fill form with tutor data
        document.getElementById('tutorFirstName').value = tutor.firstName;
        document.getElementById('tutorLastName').value = tutor.lastName;
        document.getElementById('tutorEmail').value = tutor.email;
        document.getElementById('tutorPhone').value = tutor.phone || '';
        document.getElementById('tutorQualification').value = tutor.qualification || '';
        document.getElementById('tutorExperienceYears').value = tutor.experienceYears || '';
        document.getElementById('tutorHourlyRate').value = tutor.hourlyRate || '';
        document.getElementById('tutorUsername').value = tutor.username || '';
        
        // Set specializations and expertise
        if (tutor.aiSpecializations && tutor.aiSpecializations.length > 0) {
            tutorSpecializationsInput.setTags(tutor.aiSpecializations);
        }
        
        if (tutor.domainExpertise && tutor.domainExpertise.length > 0) {
            tutorExpertiseInput.setTags(tutor.domainExpertise);
        }
    } else {
        tutorFormTitle.textContent = 'Add New Tutor';
        currentEditingTutorId = null;
    }
    
    // Show form
    tutorForm.style.display = 'block';
    addTutorBtn.style.display = 'none';
}

// Hide tutor form
function hideTutorForm() {
    tutorForm.style.display = 'none';
    addTutorBtn.style.display = 'block';
    currentEditingTutorId = null;
}

// Edit tutor
async function editTutor(tutorId) {
    try {
        const tutor = tutors.find(t => t.userId === tutorId);
        if (tutor) {
            showTutorForm(tutor);
        } else {
            // If tutor not found in local array, try to fetch it
            const fetchedTutor = await apiService.getTutorById(tutorId);
            showTutorForm(fetchedTutor);
        }
    } catch (error) {
        Toast.error('Error fetching tutor details: ' + error.message);
        console.error('Error fetching tutor details:', error);
    }
}

// Delete tutor
async function deleteTutor(tutorId) {
    try {
        await apiService.deleteTutor(tutorId);
        Toast.success('Tutor deleted successfully');
        
        // Remove from local array and update UI
        tutors = tutors.filter(t => t.userId !== tutorId);
        renderTutorsTable();
        
        // Update tutor select in session form
        updateTutorSelect();
        
        // Update dashboard
        updateDashboardStats();
    } catch (error) {
        Toast.error('Error deleting tutor: ' + error.message);
        console.error('Error deleting tutor:', error);
    }
}

// Load Sessions
async function loadSessions() {
    sessionsList.innerHTML = '';
    sessionsLoading.style.display = 'block';
    sessionsMessage.style.display = 'none';

    try {
        sessions = await apiService.getSessions();

        if (sessions.length === 0) {
            showMessage(sessionsMessage, 'No sessions found', 'info');
        } else {
            // Update session counts before rendering
            updateSessionCounts();
            renderSessionsTable();
        }
        
        // Update dashboard if needed
        updateDashboardSessions();
    } catch (error) {
        console.error('Error loading sessions:', error);
        showMessage(sessionsMessage, 'Error loading sessions: ' + error.message, 'error');
        
        // Fallback to mock data
        mockSessions();
    } finally {
        sessionsLoading.style.display = 'none';
    }
}


// Session Form Handlers
addSessionBtn.addEventListener('click', () => {
    showSessionForm();
});

closeSessionFormBtn.addEventListener('click', () => {
    hideSessionForm();
});

cancelSessionBtn.addEventListener('click', () => {
    hideSessionForm();
});

// Toggle platform field based on session type
sessionTypeRadios.forEach(radio => {
    radio.addEventListener('change', (e) => {
        if (e.target.value === 'remote') {
            platformGroup.style.display = 'block';
        } else {
            platformGroup.style.display = 'none';
        }
    });
});

// Modify your saveSessionBtn event handler
// Update the saveSessionBtn click handler
saveSessionBtn.addEventListener('click', async () => {
    const clientSelect = document.getElementById('clientSelect');
    const tutorSelect = document.getElementById('tutorSelect');
    const sessionDate = document.getElementById('sessionDate');
    const startTime = document.getElementById('startTime');
    const duration = document.getElementById('duration');
    const sessionStatus = document.getElementById('sessionStatus'); // New status dropdown
    
    if (clientSelect.value === '' || tutorSelect.value === '' || !sessionDate.value || !startTime.value) {
        Toast.error('Please fill in all required fields');
        return;
    }
    
    const isRemote = document.getElementById('remoteSession').checked;
    
    const sessionData = {
        clientId: parseInt(clientSelect.value),
        tutorId: parseInt(tutorSelect.value),
        sessionDate: sessionDate.value,
        startTime: startTime.value,
        durationMinutes: parseInt(duration.value),
        status: sessionStatus ? sessionStatus.value : 'Scheduled', // Use selected status or default to 'Scheduled'
        learningObjectives: document.getElementById('sessionObjectives').value,
        isRemote: isRemote,
        platform: isRemote ? document.getElementById('platform').value : ''
    };
    
    try {
        if (currentEditingSessionId) {
            // Update existing session
            await apiService.updateSession(currentEditingSessionId, sessionData);
            Toast.success('Session updated successfully');
        } else {
            // Add new session
            await apiService.addSession(sessionData);
            Toast.success('Session scheduled successfully');
        }
        
        // Hide form and reload sessions
        hideSessionForm();
        loadSessions();
        
        // Update clients and tutors tables to reflect updated counts
        renderClientsTable();
        renderTutorsTable();
    } catch (error) {
        Toast.error('Error: ' + error.message);
        console.error('Error saving session:', error);
    }
});

function addStatusDropdownToSessionForm() {
    // Check if the dropdown already exists
    if (document.getElementById('sessionStatus')) {
        return;
    }
    
    // Create the form group
    const formGroup = document.createElement('div');
    formGroup.className = 'form-group';
    formGroup.innerHTML = `
        <label for="sessionStatus">Session Status</label>
        <select id="sessionStatus" class="form-control">
            <option value="Scheduled">Scheduled</option>
            <option value="Completed">Completed</option>
            <option value="Cancelled">Cancelled</option>
            <option value="No-Show">No-Show</option>
            <option value="Rescheduled">Rescheduled</option>
        </select>
    `;
    
    // Find the platform group to insert before it
    const platformGroup = document.getElementById('platformGroup');
    if (platformGroup) {
        platformGroup.parentNode.insertBefore(formGroup, platformGroup);
    } else {
        // As a fallback, append to the form
        document.querySelector('#session-form .form-content').appendChild(formGroup);
    }
}

const originalShowSessionForm = showSessionForm;
window.showSessionForm = function(session = null) {
    // Call the original implementation first
    if (typeof originalShowSessionForm === 'function') {
        originalShowSessionForm(session);
    } else {
        // Fallback if originalShowSessionForm is not a function
        console.warn("Original showSessionForm is not a function, using local implementation");
        
        // Make sure we have clients and tutors loaded
        if (clients.length === 0) {
            loadClients();
        }
        
        if (tutors.length === 0) {
            loadTutors();
        }
        
        // Set today's date as minimum
        const today = new Date().toISOString().split('T')[0];
        document.getElementById('sessionDate').min = today;
        
        // Reset form
        document.getElementById('clientSelect').value = '';
        document.getElementById('tutorSelect').value = '';
        document.getElementById('sessionDate').value = today;
        document.getElementById('startTime').value = '';
        document.getElementById('duration').value = '60';
        document.getElementById('sessionObjectives').value = '';
        document.getElementById('remoteSession').checked = true;
        document.getElementById('inPersonSession').checked = false;
        platformGroup.style.display = 'block';
        document.getElementById('platform').value = 'Zoom';
        
        // Set form mode
        if (session) {
            sessionFormTitle.textContent = 'Edit Session';
            currentEditingSessionId = session.sessionId;
            
            // Fill form with session data
            document.getElementById('clientSelect').value = session.clientId;
            document.getElementById('tutorSelect').value = session.tutorId;
            document.getElementById('sessionDate').value = session.sessionDate;
            document.getElementById('startTime').value = session.startTime;
            document.getElementById('duration').value = session.durationMinutes;
            document.getElementById('sessionObjectives').value = session.learningObjectives || '';
            
            // Set session type
            if (session.isRemote) {
                document.getElementById('remoteSession').checked = true;
                document.getElementById('inPersonSession').checked = false;
                platformGroup.style.display = 'block';
                document.getElementById('platform').value = session.platform || 'Zoom';
            } else {
                document.getElementById('remoteSession').checked = false;
                document.getElementById('inPersonSession').checked = true;
                platformGroup.style.display = 'none';
            }
        } else {
            sessionFormTitle.textContent = 'Schedule New Session';
            currentEditingSessionId = null;
        }
        
        // Show form
        sessionForm.style.display = 'block';
        addSessionBtn.style.display = 'none';
    }
    
    // Add status dropdown to form
    addStatusDropdownToSessionForm();
    
    // Set status if we have a session
    if (session && document.getElementById('sessionStatus')) {
        document.getElementById('sessionStatus').value = session.status || 'Scheduled';
    }
};

const originalLoadSessions = loadSessions;
window.loadSessions = async function() {
    if (typeof originalLoadSessions === 'function') {
        await originalLoadSessions();
    } else {
        // Fallback implementation
        console.warn("Original loadSessions is not a function, using fallback");
        
        sessionsList.innerHTML = '';
        sessionsLoading.style.display = 'block';
        sessionsMessage.style.display = 'none';

        try {
            sessions = await apiService.getSessions();

            if (sessions.length === 0) {
                showMessage(sessionsMessage, 'No sessions found', 'info');
            } else {
                renderSessionsTable();
            }
            
            // Update dashboard if needed
            updateDashboardSessions();
        } catch (error) {
            console.error('Error loading sessions:', error);
            showMessage(sessionsMessage, 'Error loading sessions: ' + error.message, 'error');
            
            // Fallback to mock data
            mockSessions();
        } finally {
            sessionsLoading.style.display = 'none';
        }
    }
    
    // Run updateSessionCounts after sessions are loaded
    updateSessionCounts();
};


function updateSessionCounts() {
    // Reset all counts first
    clients.forEach(client => {
        client.sessionsCompleted = 0;
    });
    
    tutors.forEach(tutor => {
        tutor.sessionsCompleted = 0;
    });
    
    // Count completed sessions for each client and tutor
    sessions.forEach(session => {
        if (session.status === 'Completed') {
            // Update client session count
            const client = clients.find(c => c.clientId === session.clientId);
            if (client) {
                client.sessionsCompleted = (client.sessionsCompleted || 0) + 1;
            }
            
            // Update tutor session count
            const tutor = tutors.find(t => t.userId === session.tutorId);
            if (tutor) {
                tutor.sessionsCompleted = (tutor.sessionsCompleted || 0) + 1;
            }
        }
    });
    
    // Update UI if needed
    if (clientsList.innerHTML) {
        renderClientsTable();
    }
    if (tutorsList.innerHTML) {
        renderTutorsTable();
    }
    
    // Update dashboard stats if visible
    if (document.getElementById('dashboard-panel').classList.contains('active')) {
        updateDashboardStats();
    }
}


/// Update showSessionForm to include status dropdown
function showSessionForm(session = null) {
    // Make sure we have clients and tutors loaded
    if (clients.length === 0) {
        loadClients();
    }
    
    if (tutors.length === 0) {
        loadTutors();
    }
    
    // Add status dropdown if not already present
    addStatusDropdownToSessionForm();
    
    // Set today's date as minimum
    const today = new Date().toISOString().split('T')[0];
    document.getElementById('sessionDate').min = today;
    
    // Reset form
    document.getElementById('clientSelect').value = '';
    document.getElementById('tutorSelect').value = '';
    document.getElementById('sessionDate').value = today;
    document.getElementById('startTime').value = '';
    document.getElementById('duration').value = '60';
    document.getElementById('sessionObjectives').value = '';
    document.getElementById('sessionStatus').value = 'Scheduled'; // Set default status
    document.getElementById('remoteSession').checked = true;
    document.getElementById('inPersonSession').checked = false;
    platformGroup.style.display = 'block';
    document.getElementById('platform').value = 'Zoom';
    
    // Set form mode
    if (session) {
        sessionFormTitle.textContent = 'Edit Session';
        currentEditingSessionId = session.sessionId;
        
        // Fill form with session data
        document.getElementById('clientSelect').value = session.clientId;
        document.getElementById('tutorSelect').value = session.tutorId;
        document.getElementById('sessionDate').value = session.sessionDate;
        document.getElementById('startTime').value = session.startTime;
        document.getElementById('duration').value = session.durationMinutes;
        document.getElementById('sessionObjectives').value = session.learningObjectives || '';
        document.getElementById('sessionStatus').value = session.status; // Set status from session
        
        // Set session type
        if (session.isRemote) {
            document.getElementById('remoteSession').checked = true;
            document.getElementById('inPersonSession').checked = false;
            platformGroup.style.display = 'block';
            document.getElementById('platform').value = session.platform || 'Zoom';
        } else {
            document.getElementById('remoteSession').checked = false;
            document.getElementById('inPersonSession').checked = true;
            platformGroup.style.display = 'none';
        }
    } else {
        sessionFormTitle.textContent = 'Schedule New Session';
        currentEditingSessionId = null;
    }
    
    // Show form
    sessionForm.style.display = 'block';
    addSessionBtn.style.display = 'none';
}

// Hide session form
function hideSessionForm() {
    sessionForm.style.display = 'none';
    addSessionBtn.style.display = 'block';
    currentEditingSessionId = null;
}

// Edit session
function editSession(sessionId) {
    const session = sessions.find(s => s.sessionId === sessionId);
    if (session) {
        showSessionForm(session);
    } else {
        Toast.error('Session not found');
    }
}


apiService.updateSession = async function(sessionId, sessionData) {
    console.log('Updating session:', sessionId, sessionData);
    
    if (this.mockMode) {
        // In mock mode, update the session in the local array
        const index = sessions.findIndex(s => s.sessionId === parseInt(sessionId));
        if (index === -1) {
            console.error('Session not found');
            throw new Error('Session not found');
        }
        
        // Store the old status before updating
        const oldStatus = sessions[index].status;
        
        // Update the session
        sessions[index] = {
            ...sessions[index],
            ...sessionData
        };
        
        console.log('Updated session:', sessions[index]);
        
        // If status changed to/from 'Completed', update the session counts
        if (oldStatus !== sessionData.status && 
            (oldStatus === 'Completed' || sessionData.status === 'Completed')) {
            updateSessionCounts();
        }
        
        return sessions[index];
    }
    
    try {
        const response = await fetch(`${this.baseUrl}/sessions/${sessionId}`, {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(sessionData)
        });
        
        if (!response.ok) {
            const errorText = await response.text();
            console.error('API error:', errorText);
            throw new Error(`API error: ${response.status} ${errorText}`);
        }
        
        const result = await response.json();
        
        // Update the local cache
        const sessionIndex = sessions.findIndex(s => s.sessionId === parseInt(sessionId));
        if (sessionIndex !== -1) {
            const oldStatus = sessions[sessionIndex].status;
            sessions[sessionIndex] = { ...sessions[sessionIndex], ...sessionData };
            
            // If status changed to/from 'Completed', update the session counts
            if (oldStatus !== sessionData.status && 
                (oldStatus === 'Completed' || sessionData.status === 'Completed')) {
                updateSessionCounts();
            }
        }
        
        return result;
    } catch (error) {
        console.error('Error updating session:', error);
        throw error;
    }
};

// Enhance the cancelSession method in apiService to update counts
apiService.cancelSession = async function(sessionId) {
    if (this.mockMode) {
        console.log('Canceling mock session', sessionId);
        const index = sessions.findIndex(s => s.sessionId === sessionId);
        if (index === -1) throw new Error('Session not found');
        
        // Store the old status
        const oldStatus = sessions[index].status;
        sessions[index].status = 'Cancelled';
        
        // If the session was previously completed, update counts
        if (oldStatus === 'Completed') {
            updateSessionCounts();
        }
        
        return { success: true, message: 'Session cancelled' };
    }
    
    try {
        const response = await fetch(`${this.baseUrl}/sessions/${sessionId}/cancel`, {
            method: 'POST'
        });

        if (!response.ok) throw new Error('Failed to cancel session');
        const result = await response.json();
        
        // Update local session and check if status changed from 'Completed'
        const session = sessions.find(s => s.sessionId === sessionId);
        if (session) {
            const oldStatus = session.status;
            session.status = 'Cancelled';
            
            // If the session was previously completed, update counts
            if (oldStatus === 'Completed') {
                updateSessionCounts();
            }
        }
        
        return result;
    } catch (error) {
        console.error(`Error canceling session ${sessionId}:`, error);
        throw error;
    }
};

// Load Materials
async function loadMaterials() {
    materialsList.innerHTML = '';
    materialsLoading.style.display = 'block';
    materialsMessage.style.display = 'none';

    try {
        materials = await apiService.getMaterials();

        if (materials.length === 0) {
            showMessage(materialsMessage, 'No learning materials found', 'info');
        } else {
            renderMaterialsTable();
        }
        
        // Update dashboard if needed
        updateDashboardMaterials();
    } catch (error) {
        console.error('Error loading materials:', error);
        showMessage(materialsMessage, 'Error loading materials: ' + error.message, 'error');
        
        // Fallback to mock data
        mockMaterials();
    } finally {
        materialsLoading.style.display = 'none';
    }
}

// Render materials table
function renderMaterialsTable() {
    materialsList.innerHTML = '';
    
    materials.forEach(material => {
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${material.title}</td>
            <td>${material.type}</td>
            <td>${material.format}</td>
            <td>${material.author}</td>
            <td>${getDifficultyText(material.difficultyLevel)} (${material.difficultyLevel}/5)</td>
            <td>${formatMinutes(material.estimatedTimeMinutes)}</td>
            <td class="action-icons">
                <i class="fas fa-edit action-icon" data-id="${material.materialId}"></i>
                <i class="fas fa-trash action-icon delete" data-id="${material.materialId}"></i>
            </td>
        `;
        materialsList.appendChild(row);
    });
    
    // Add event listeners for edit/delete icons
    materialsList.querySelectorAll('.fa-edit').forEach(icon => {
        icon.addEventListener('click', () => {
            const materialId = parseInt(icon.dataset.id);
            editMaterial(materialId);
        });
    });
    
    materialsList.querySelectorAll('.fa-trash').forEach(icon => {
        icon.addEventListener('click', () => {
            const materialId = parseInt(icon.dataset.id);
            if (confirm('Are you sure you want to delete this material?')) {
                deleteMaterial(materialId);
            }
        });
    });
}

// Material Form Handlers
addMaterialBtn.addEventListener('click', () => {
    showMaterialForm();
});

closeMaterialFormBtn.addEventListener('click', () => {
    hideMaterialForm();
});

cancelMaterialBtn.addEventListener('click', () => {
    hideMaterialForm();
});

saveMaterialBtn.addEventListener('click', async () => {
    const title = document.getElementById('materialTitle').value;
    const author = document.getElementById('materialAuthor').value;
    const type = document.getElementById('materialType').value;
    const format = document.getElementById('materialFormat').value;
    
    if (!title || !author || !type || !format) {
        Toast.error('Please fill in all required fields');
        return;
    }
    
    const materialData = {
        title: title,
        author: author,
        description: document.getElementById('materialDescription').value,
        type: type,
        format: format,
        difficultyLevel: parseInt(document.getElementById('materialDifficulty').value),
        estimatedTimeMinutes: parseInt(document.getElementById('materialTime').value),
        url: document.getElementById('materialUrl').value,
        localPath: document.getElementById('materialPath').value,
        tags: materialTagsInput ? materialTagsInput.getTags() : [],
        aiModelIds: getSelectedAIModelIds()
    };
    
    try {
        if (currentEditingMaterialId) {
            // Update existing material
            await apiService.updateMaterial(currentEditingMaterialId, materialData);
            Toast.success('Material updated successfully');
        } else {
            // Add new material
            await apiService.addMaterial(materialData);
            Toast.success('Material added successfully');
        }
        
        // Hide form and reload materials
        hideMaterialForm();
        loadMaterials();
    } catch (error) {
        Toast.error('Error: ' + error.message);
        console.error('Error saving material:', error);
    }
});

// Get selected AI model IDs from checkboxes
function getSelectedAIModelIds() {
    const selectedIds = [];
    const checkboxes = document.querySelectorAll('#materialAIModelsSelect input[type="checkbox"]');
    
    checkboxes.forEach(checkbox => {
        if (checkbox.checked) {
            selectedIds.push(parseInt(checkbox.value));
        }
    });
    
    return selectedIds;
}

// Show material form for adding or editing
function showMaterialForm(material = null) {
    // Make sure we have AI models loaded
    if (aiModels.length === 0) {
        loadAIModels();
    }
    
    // Reset form
    document.getElementById('materialTitle').value = '';
    document.getElementById('materialAuthor').value = '';
    document.getElementById('materialDescription').value = '';
    document.getElementById('materialType').value = 'Document';
    document.getElementById('materialFormat').value = 'PDF';
    document.getElementById('materialDifficulty').value = '3';
    document.getElementById('materialTime').value = '60';
    document.getElementById('materialUrl').value = '';
    document.getElementById('materialPath').value = '';
    
    // Initialize tag input if needed
    if (!materialTagsInput) {
        materialTagsInput = new TagInput(document.getElementById('materialTags'));
    } else {
        materialTagsInput.setTags([]);
    }
    
    // Update AI models checkboxes
    updateAIModelCheckboxes(material ? material.aiModelIds : []);
    
    // Set form mode
    if (material) {
        materialFormTitle.textContent = 'Edit Learning Material';
        currentEditingMaterialId = material.materialId;
        
        // Fill form with material data
        document.getElementById('materialTitle').value = material.title;
        document.getElementById('materialAuthor').value = material.author;
        document.getElementById('materialDescription').value = material.description || '';
        document.getElementById('materialType').value = material.type;
        document.getElementById('materialFormat').value = material.format;
        document.getElementById('materialDifficulty').value = material.difficultyLevel || '3';
        document.getElementById('materialTime').value = material.estimatedTimeMinutes || '60';
        document.getElementById('materialUrl').value = material.url || '';
        document.getElementById('materialPath').value = material.localPath || '';
        
        // Set tags
        if (material.tags && material.tags.length > 0) {
            materialTagsInput.setTags(material.tags);
        }
    } else {
        materialFormTitle.textContent = 'Add New Learning Material';
        currentEditingMaterialId = null;
    }
    
    // Show form
    materialForm.style.display = 'block';
    addMaterialBtn.style.display = 'none';
}

// Update AI model checkboxes in material form
function updateAIModelCheckboxes(selectedIds = []) {
    const container = document.getElementById('materialAIModelsSelect');
    
    if (aiModels.length === 0) {
        container.innerHTML = '<div class="loading-inline"><i class="fas fa-spinner fa-spin"></i> Loading AI models...</div>';
        return;
    }
    
    container.innerHTML = '';
    
    aiModels.forEach(model => {
        const isChecked = selectedIds.includes(model.modelId);
        
        const checkbox = document.createElement('div');
        checkbox.className = 'checkbox-option';
        checkbox.innerHTML = `
            <input type="checkbox" id="model-${model.modelId}" value="${model.modelId}" ${isChecked ? 'checked' : ''}>
            <label for="model-${model.modelId}">${model.name} (${model.category})</label>
        `;
        
        container.appendChild(checkbox);
    });
}

// Hide material form
function hideMaterialForm() {
    materialForm.style.display = 'none';
    addMaterialBtn.style.display = 'block';
    currentEditingMaterialId = null;
}

// Edit material
function editMaterial(materialId) {
    const material = materials.find(m => m.materialId === materialId);
    if (material) {
        showMaterialForm(material);
    } else {
        Toast.error('Material not found');
    }
}

// Delete material
async function deleteMaterial(materialId) {
    try {
        await apiService.deleteMaterial(materialId);
        Toast.success('Material deleted successfully');
        
        // Remove from local array and update UI
        materials = materials.filter(m => m.materialId !== materialId);
        renderMaterialsTable();
        
        // Update dashboard
        updateDashboardMaterials();
    } catch (error) {
        Toast.error('Error deleting material: ' + error.message);
        console.error('Error deleting material:', error);
    }
}

// Update client select in session form
function updateClientSelect() {
    const clientSelect = document.getElementById('clientSelect');
    clientSelect.innerHTML = '<option value="">Select a client</option>';
    
    clients.forEach(client => {
        const option = document.createElement('option');
        option.value = client.clientId;
        option.textContent = `${client.firstName} ${client.lastName}`;
        clientSelect.appendChild(option);
    });
}

// Update tutor select in session form
function updateTutorSelect() {
    const tutorSelect = document.getElementById('tutorSelect');
    tutorSelect.innerHTML = '<option value="">Select a tutor</option>';
    
    tutors.forEach(tutor => {
        const option = document.createElement('option');
        option.value = tutor.userId;
        option.textContent = `${tutor.firstName} ${tutor.lastName}`;
        tutorSelect.appendChild(option);
    });
}

// Load AI Models
async function loadAIModels() {
    try {
        aiModels = await apiService.getAIModels();
        
        // Update AI model checkboxes in material form
        updateAIModelCheckboxes();
    } catch (error) {
        console.error('Error loading AI models:', error);
        Toast.error('Error loading AI models: ' + error.message);
        
        // Mock data fallback
        aiModels = [
            { modelId: 1, name: 'GPT-4', category: 'Large Language Model' },
            { modelId: 2, name: 'DALL-E 3', category: 'Image Generation' },
            { modelId: 3, name: 'Claude', category: 'Large Language Model' }
        ];
    }
}

// Update Dashboard
function updateDashboard() {
    updateDashboardStats();
    updateDashboardSessions();
    updateDashboardMaterials();
}

// Update dashboard statistics
function updateDashboardStats() {
    totalClientsCount.textContent = clients.length;
    totalTutorsCount.textContent = tutors.length;
    
    // Count sessions this month
    const thisMonth = new Date().getMonth() + 1;
    const thisYear = new Date().getFullYear();
    
    let monthSessions = 0;
    let monthRevenue = 0;
    
    sessions.forEach(session => {
        const sessionDate = new Date(session.sessionDate);
        if (sessionDate.getMonth() + 1 === thisMonth && sessionDate.getFullYear() === thisYear) {
            monthSessions++;
            monthRevenue += session.sessionCost || 0;
        }
    });
    
    sessionsThisMonth.textContent = monthSessions;
    revenueThisMonth.textContent = `$${monthRevenue.toFixed(2)}`;
}

// Update dashboard sessions
function updateDashboardSessions() {
    // Show upcoming sessions in the dashboard
    dashboardSessionsList.innerHTML = '';
    
    // Get today's date
    const today = new Date();
    today.setHours(0, 0, 0, 0);
    
    // Filter upcoming sessions and sort by date
    const upcomingSessions = sessions
        .filter(session => {
            const sessionDate = new Date(session.sessionDate);
            sessionDate.setHours(0, 0, 0, 0);
            return sessionDate >= today && session.status === 'Scheduled';
        })
        .sort((a, b) => {
            const dateA = new Date(a.sessionDate + 'T' + a.startTime);
            const dateB = new Date(b.sessionDate + 'T' + b.startTime);
            return dateA - dateB;
        })
        .slice(0, 5); // Show only next 5 sessions
    
    if (upcomingSessions.length === 0) {
        dashboardSessionsList.innerHTML = `
            <tr>
                <td colspan="5" class="loading-message">
                    No upcoming sessions
                </td>
            </tr>
        `;
        return;
    }
    
    upcomingSessions.forEach(session => {
        const client = clients.find(c => c.clientId === session.clientId);
        const tutor = tutors.find(t => t.userId === session.tutorId);
        
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${formatDate(session.sessionDate)}</td>
            <td>${session.startTime} - ${calculateEndTime(session.startTime, session.durationMinutes)}</td>
            <td>${client ? client.firstName + ' ' + client.lastName : 'Unknown Client'}</td>
            <td>${tutor ? tutor.firstName + ' ' + tutor.lastName : 'Unknown Tutor'}</td>
            <td>${session.isRemote ? session.platform : 'In-Person'}</td>
        `;
        dashboardSessionsList.appendChild(row);
    });
}

// Update dashboard materials
function updateDashboardMaterials() {
    // Show popular materials in the dashboard
    popularMaterialsList.innerHTML = '';
    
    // Sort materials by rating or usage count
    const topMaterials = [...materials]
        .sort((a, b) => {
            // First sort by rating
            if (b.rating !== a.rating) {
                return b.rating - a.rating;
            }
            // Then by usage count
            return b.usageCount - a.usageCount;
        })
        .slice(0, 6); // Show top 6 materials
    
    if (topMaterials.length === 0) {
        popularMaterialsList.innerHTML = `
            <div class="loading-container">
                No learning materials available
            </div>
        `;
        return;
    }
    
    topMaterials.forEach(material => {
        const card = document.createElement('div');
        card.className = 'material-card';
        card.innerHTML = `
            <span class="material-type">${material.type}</span>
            <h4>${material.title}</h4>
            <div class="material-info">
                <span>${getDifficultyText(material.difficultyLevel)}</span>
                <span>${formatMinutes(material.estimatedTimeMinutes)}</span>
            </div>
        `;
        popularMaterialsList.appendChild(card);
    });
}

// Utility Functions
function showMessage(element, message, type) {
    element.textContent = message;
    element.className = `message ${type}`;
    element.style.display = 'block';
    
    // Hide message after 5 seconds
    setTimeout(() => {
        element.style.display = 'none';
    }, 5000);
}

// Check database connection
async function checkDatabaseConnection() {
    try {
        const response = await fetch(`${apiService.baseUrl}/health/database`);
        const data = await response.json();
        
        if (data.status === "connected") {
            Toast.success("Database connected successfully");
            return true;
        } else {
            Toast.warning(`Database not connected: ${data.message || "Unknown error"}`);
            return false;
        }
    } catch (error) {
        Toast.error("Failed to check database connection");
        console.error("Error checking database:", error);
        return false;
    }
}

// Mock Data Fallbacks
function mockClients() {
    clients = [
        {
            clientId: 1,
            firstName: 'John',
            lastName: 'Smith',
            email: 'john.smith@example.com',
            phone: '555-123-4567',
            company: 'Tech Innovations',
            position: 'Data Scientist',
            aiModelsOfInterest: ['GPT-4', 'DALL-E'],
            registrationDate: '2025-04-01',
            sessionsCompleted: 2,
            budget: 1000
        },
        {
            clientId: 2,
            firstName: 'Sarah',
            lastName: 'Davis',
            email: 'sarah.davis@example.com',
            phone: '555-987-6543',
            company: 'AI Solutions',
            position: 'Project Manager',
            aiModelsOfInterest: ['Claude AI'],
            registrationDate: '2025-04-05',
            sessionsCompleted: 1,
            budget: 2000
        },
        {
            clientId: 3,
            firstName: 'Ahmed',
            lastName: 'Hassan',
            email: 'ahmed.hassan@example.com',
            phone: '555-456-7890',
            company: 'Innovate Inc.',
            position: 'CTO',
            aiModelsOfInterest: ['GPT-4', 'DALL-E', 'Stable Diffusion'],
            registrationDate: '2025-04-08',
            sessionsCompleted: 0,
            budget: 5000
        }
    ];
    
    renderClientsTable();
    updateClientSelect();
    updateDashboardStats();
}

function mockTutors() {
    tutors = [
        {
            userId: 1,
            firstName: 'Emily',
            lastName: 'Johnson',
            email: 'emily.johnson@aitutoring.com',
            phone: '555-111-2222',
            aiSpecializations: ['GPT-4', 'DALL-E', 'Claude AI'],
            domainExpertise: ['Natural Language Processing', 'Neural Networks'],
            qualification: 'PhD in Computer Science',
            experienceYears: 5,
            hourlyRate: 120,
            sessionsCompleted: 32,
            averageRating: 4.8
        },
        {
            userId: 2,
            firstName: 'Michael',
            lastName: 'Lee',
            email: 'michael.lee@aitutoring.com',
            phone: '555-333-4444',
            aiSpecializations: ['Claude AI', 'LLaMA'],
            domainExpertise: ['Large Language Models', 'Prompt Engineering'],
            qualification: 'MS in AI',
            experienceYears: 3,
            hourlyRate: 90,
            sessionsCompleted: 15,
            averageRating: 4.5
        },
        {
            userId: 3,
            firstName: 'James',
            lastName: 'Wilson',
            email: 'james.wilson@aitutoring.com',
            phone: '555-555-6666',
            aiSpecializations: ['Midjourney', 'Stable Diffusion'],
            domainExpertise: ['Generative Art', 'Computer Vision'],
            qualification: 'BS in Computer Science',
            experienceYears: 4,
            hourlyRate: 100,
            sessionsCompleted: 24,
            averageRating: 4.7
        }
    ];
    
    
    renderTutorsTable();
    updateTutorSelect();
    updateDashboardStats();
}

function mockSessions() {
    if (clients.length === 0) mockClients();
    if (tutors.length === 0) mockTutors();
    
    sessions = [
        {
            sessionId: 1,
            clientId: 1,
            tutorId: 1,
            aiModelIds: [],
            sessionDate: '2025-04-25',
            startTime: '14:00',
            durationMinutes: 90,
            status: 'Scheduled',
            learningObjectives: 'Introduction to GPT-4 architecture and capabilities',
            isRemote: true,
            platform: 'Zoom',
            sessionCost: 180
        },
        {
            sessionId: 2,
            clientId: 2,
            tutorId: 2,
            aiModelIds: [],
            sessionDate: '2025-04-26',
            startTime: '10:00',
            durationMinutes: 120,
            status: 'Scheduled',
            learningObjectives: 'Advanced prompting techniques for Claude AI',
            isRemote: true,
            platform: 'Microsoft Teams',
            sessionCost: 180
        },
        {
            sessionId: 3,
            clientId: 1,
            tutorId: 1,
            aiModelIds: [],
            sessionDate: '2025-04-15',
            startTime: '09:00',
            durationMinutes: 60,
            status: 'Completed',
            clientRating: 4.5,
            isRemote: false,
            sessionCost: 120
        }
    ];
    
    renderSessionsTable();
    updateDashboardSessions();
    updateDashboardStats();
}

function mockMaterials() {
    materials = [
        {
            materialId: 1,
            title: 'GPT-4 Architecture Overview',
            type: 'Document',
            format: 'PDF',
            author: 'Dr. Emily Johnson',
            difficultyLevel: 3,
            estimatedTimeMinutes: 45,
            rating: 4.7,
            usageCount: 12,
            tags: ['GPT-4', 'Architecture', 'Large Language Models']
        },
        {
            materialId: 2,
            title: 'Prompt Engineering Masterclass',
            type: 'Video',
            format: 'MP4',
            author: 'Michael Lee',
            difficultyLevel: 2,
            estimatedTimeMinutes: 120,
            rating: 4.9,
            usageCount: 25,
            tags: ['Prompt Engineering', 'Best Practices', 'Tutorials']
        },
        {
            materialId: 3,
            title: 'Image Generation Fundamentals',
            type: 'Interactive',
            format: 'Notebook',
            author: 'James Wilson',
            difficultyLevel: 2,
            estimatedTimeMinutes: 90,
            rating: 4.6,
            usageCount: 18,
            tags: ['Image Generation', 'Tutorial', 'Notebook']
        },
        {
            materialId: 4,
            title: 'Advanced LLM Fine-tuning',
            type: 'Document',
            format: 'PDF',
            author: 'Dr. Emily Johnson',
            difficultyLevel: 4,
            estimatedTimeMinutes: 60,
            rating: 4.8,
            usageCount: 15,
            tags: ['Fine-tuning', 'Advanced', 'LLMs']
        }
    ];
    
    renderMaterialsTable();
    updateDashboardMaterials();
}

document.addEventListener('DOMContentLoaded', function() {
    const aboutBtn = document.getElementById('about-btn');
    const aboutModal = document.getElementById('about-modal');
    const closeModal = document.getElementById('close-modal');
    
    if (aboutBtn && aboutModal) {
      // Open modal when about button is clicked
      aboutBtn.addEventListener('click', function() {
        aboutModal.classList.add('show');
        document.body.style.overflow = 'hidden'; // Prevent scrolling when modal is open
        
        // Animate letters when modal opens
        setTimeout(animateAuraiLetters, 300);
      });
      
      // Close modal when close button is clicked
      if (closeModal) {
        closeModal.addEventListener('click', function() {
          aboutModal.classList.remove('show');
          document.body.style.overflow = ''; // Restore scrolling
        });
      }
      
      // Close modal when clicking outside the content
      aboutModal.addEventListener('click', function(e) {
        if (e.target === aboutModal) {
          aboutModal.classList.remove('show');
          document.body.style.overflow = ''; // Restore scrolling
        }
      });
      
      // Close modal with Escape key
      document.addEventListener('keydown', function(e) {
        if (e.key === 'Escape' && aboutModal.classList.contains('show')) {
          aboutModal.classList.remove('show');
          document.body.style.overflow = ''; // Restore scrolling
        }
      });
    }
  });

// Modify the existing document ready event listener to include export buttons
document.addEventListener('DOMContentLoaded', function() {
 
    loadClients();
    loadTutors();
    loadSessions();
    loadMaterials();
    loadAIModels();
    initializeSearchFunctionality();
    
    // Add export buttons
    addExportButtons();
    
    // Set today as the minimum date for session scheduling
    const today = new Date().toISOString().split('T')[0];
    const sessionDateInput = document.getElementById('sessionDate');
    if (sessionDateInput) {
        sessionDateInput.min = today;
    }
    
});