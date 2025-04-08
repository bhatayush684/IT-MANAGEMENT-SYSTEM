// Predefined login credentials
const credentials = {
    username: 'admin123',
    password: 'password123'
};

// Show login page and hide inventory page
function showLoginPage() {
    document.getElementById('loginPage').style.display = 'block';
    document.getElementById('inventoryPage').style.display = 'none';
}

// Show inventory page and hide login page
function showInventoryPage() {
    document.getElementById('loginPage').style.display = 'none';
    document.getElementById('inventoryPage').style.display = 'block';
}

// Handle login submission
document.getElementById('loginForm').addEventListener('submit', function (e) {
    e.preventDefault();

    const username = document.getElementById('username').value;
    const password = document.getElementById('password').value;

    if (username === credentials.username && password === credentials.password) {
        showInventoryPage();
    } else {
        document.getElementById('loginError').innerText = 'Invalid credentials, please try again.';
    }
});

// Logout
document.getElementById('logoutBtn').addEventListener('click', function () {
    showLoginPage();
});

// Show Add Asset form
function showAddAssetForm() {
    document.getElementById('assetForm').style.display = 'block';
    document.getElementById('inventoryList').style.display = 'none';
}

// Show Inventory list
function showInventory() {
    document.getElementById('inventoryList').style.display = 'block';
    document.getElementById('assetForm').style.display = 'none';
    updateInventoryTable();
}

// Add asset (mock)
document.getElementById('assetFormDetails').addEventListener('submit', function (e) {
    e.preventDefault();
    const assetName = document.getElementById('assetName').value;
    alert('Asset ' + assetName + ' added!');
    showInventory();
});

// Mock function to update inventory table
function updateInventoryTable() {
    const inventoryTable = document.getElementById('inventoryTable');
    inventoryTable.innerHTML = `<tr><th>Asset Name</th><th>Type</th><th>Action</th></tr>`;
    const newRow = inventoryTable.insertRow(1);
    newRow.insertCell(0).innerText = 'Laptop 1';
    newRow.insertCell(1).innerText = 'Laptop';
    newRow.insertCell(2).innerHTML = '<button onclick="editAsset()">Edit</button>';
}

// Edit asset (mock)
function editAsset() {
    alert('Edit Asset');
}

// Delete asset (mock)
function deleteAsset() {
    alert('Delete Asset');
}

// Initialize the login page
showLoginPage();
