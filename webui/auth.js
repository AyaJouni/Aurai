// auth.js - Simple authentication handler

// Check if user is authenticated
function checkAuth() {
    const authenticated = localStorage.getItem('authenticated');
    
    if (!authenticated || authenticated !== 'true') {
        // Redirect to login page if not authenticated
        window.location.href = 'login.html';
        return false;
    }
    
    return true;
}

// Setup logout functionality
function setupLogout() {
    const logoutBtn = document.getElementById('logout-btn');
    if (logoutBtn) {
        logoutBtn.addEventListener('click', function() {
            // Clear authentication state
            localStorage.removeItem('authenticated');
            localStorage.removeItem('user');
            
            // Redirect to login page
            window.location.href = 'login.html';
        });
    }
}

// Run when page loads
document.addEventListener('DOMContentLoaded', function() {
    // Verify authentication first
    if (checkAuth()) {
        // If authenticated, setup logout and continue
        setupLogout();
        
        // Display username if available
        const userInfo = JSON.parse(localStorage.getItem('user') || '{}');
        const userNameElement = document.querySelector('.user-name');
        if (userNameElement && userInfo.name) {
            userNameElement.textContent = userInfo.name;
        }
    }
});