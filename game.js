const game = {
    currentCity: null,
    // challenge=闯关模式 free=自由模式 custom=自定义
    mode: 'challenge',
    data: {
        city: '',
        lines: {},
        districts: {},
        stations: [],
        nameMap: new Map(),
        adj: []
    },
    state: {
        answerId: -1,
        maxAttempts: 6,
        currentAttempt: 0,
        guesses: [],
        isGameOver: false,
        isWin: false
    },
    challenge: {
        currentLevel: 1,
        levelList: [],
        passedLevels: []
    },
    distanceCache: {
        station: new Map(),
        transfer: new Map()
    }
};

// 初始化基础数据
function initData() {
    document.getElementById('station-input').addEventListener('keydown', (e) => {
        if (e.key === 'Enter') submitGuess();
    });
    bindModalEvents();
}

// 选择城市
function selectCity(cityId) {
    game.currentCity = cityId;
    const city = cityData[cityId];

    game.data.city = city.name;
    game.data.lines = city.lines;
    game.data.districts = city.districts;
    game.data.stations = city.stations;
    game.state.maxAttempts = city.maxAttempts || 6;
    
    game.data.nameMap.clear();
    game.data.adj = [];
    game.data.stations.forEach(station => {
        game.data.nameMap.set(station.name, station.id);
        const l=station.name.indexOf('(');
        if(l!=-1){
            game.data.nameMap.set(station.name.slice(l+1,-1),station.id);
            game.data.nameMap.set(station.name.slice(0,l),station.id);
        }
        game.data.adj[station.id] = station.neighbors;
    });
    
    document.getElementById('game-title').textContent = city.title;
    document.getElementById('city-select-screen').classList.add('hidden');
    document.getElementById('game-screen').classList.remove('hidden');
    renderEmptyRows();
    initChallengeMode();
}

// 返回城市选择
function backToCitySelect() {
    if (game.currentCity) {
        localStorage.removeItem(`metro_challenge_progress_${game.currentCity}`);
    }
    
    game.currentCity = null;
    game.state = {
        answerId: -1,
        maxAttempts: 6,
        currentAttempt: 0,
        guesses: [],
        isGameOver: false,
        isWin: false
    };
    game.challenge = {
        currentLevel: 1,
        levelList: [],
        passedLevels: []
    };
    
    // 切换界面
    document.getElementById('game-screen').classList.add('hidden');
    document.getElementById('city-select-screen').classList.remove('hidden');
    document.getElementById('result-modal').classList.add('hidden');
}

// 初始化闯关模式
function initChallengeMode(restart = false) {
    game.mode = 'challenge';
    const totalLevels = game.data.stations.length;
    const storageKey = `metro_challenge_progress_${game.currentCity}`;
    
    if (restart || game.challenge.levelList.length === 0) {
        game.challenge.levelList = [...game.data.stations].sort(() => Math.random() - 0.5).map(s => s.id);
        game.challenge.currentLevel = 1;
        game.challenge.passedLevels = [];
        localStorage.removeItem(storageKey);
    } else {
        const savedProgress = localStorage.getItem(storageKey);
        if (savedProgress) {
            const saved = JSON.parse(savedProgress);
            game.challenge = saved;
        }
    }

    const currentLevelIndex = game.challenge.currentLevel - 1;
    game.state.answerId = game.challenge.levelList[currentLevelIndex];
    
    resetGameState();
    updateChallengeUI();
}

// 进入下一关
function goNextLevel() {
    if (!game.challenge.passedLevels.includes(game.challenge.currentLevel)) {
        game.challenge.passedLevels.push(game.challenge.currentLevel);
    }
    
    const totalLevels = game.challenge.levelList.length;
    if (game.challenge.currentLevel >= totalLevels) {
        showAllClearModal();
        return;
    }

    game.challenge.currentLevel++;
    const storageKey = `metro_challenge_progress_${game.currentCity}`;
    localStorage.setItem(storageKey, JSON.stringify(game.challenge));
    
    game.state.answerId = game.challenge.levelList[game.challenge.currentLevel - 1];
    resetGameState();
    updateChallengeUI();
    document.getElementById('result-modal').classList.add('hidden');
}

// 重玩当前关卡
function retryCurrentLevel() {
    game.state.answerId = game.challenge.levelList[game.challenge.currentLevel - 1];
    resetGameState();
    document.getElementById('result-modal').classList.add('hidden');
}

// 更新闯关模式UI
function updateChallengeUI() {
    const totalLevels = game.challenge.levelList.length;
    document.getElementById('level-desc').textContent = `闯关模式 - 猜出当前关卡隐藏地铁站`;
    document.getElementById('level-progress').textContent = `第 ${game.challenge.currentLevel} 关 / 共 ${totalLevels} 关`;
    document.getElementById('modal-level-progress').textContent = `当前进度：第 ${game.challenge.currentLevel} 关 / 共 ${totalLevels} 关`;
    updateGameStatus();
}

// 重置游戏状态
function resetGameState() {
    const currentMaxAttempts = game.state.maxAttempts;
    
    game.state.currentAttempt = 0;
    game.state.guesses = [];
    game.state.isGameOver = false;
    game.state.isWin = false;
    game.distanceCache.station.clear();
    game.distanceCache.transfer.clear();
    game.state.maxAttempts = currentMaxAttempts;
    
    bfs(game.state.answerId, 'station');
    bfs(game.state.answerId, 'transfer');
    game.data.nameMap.set('\\' , game.state.answerId);

    renderEmptyRows();
    updateGameStatus();
    document.getElementById('station-input').value = '';
    document.getElementById('submit-btn').disabled = false;
    document.getElementById('result-modal').classList.add('hidden');
}

// BFS计算距离
function bfs(startId, type) {
    const queue = [startId];
    const visited = new Set([startId]);
    const distance = new Map();
    distance.set(startId, 0);

    while (queue.length > 0) {
        const current = queue.shift();
        const currentStation = game.data.stations.find(s => s.id === current);
        
        if (type === 'station') {
            game.data.adj[current].forEach(neighbor => {
                if (!visited.has(neighbor)) {
                    visited.add(neighbor);
                    distance.set(neighbor, distance.get(current) + 1);
                    queue.push(neighbor);
                }
            });
        }

        if (type === 'transfer') {
            game.data.stations.forEach(station => {
                if (!visited.has(station.id)) {
                    const hasCommonLine = currentStation.lines.some(line => station.lines.includes(line));
                    if (hasCommonLine) {
                        visited.add(station.id);
                        distance.set(station.id, distance.get(current) + 1);
                        queue.push(station.id);
                    }
                }
            });
        }
    }

    if (type === 'station') game.distanceCache.station = distance;
    if (type === 'transfer') game.distanceCache.transfer = distance;
}

// 渲染空的猜测行
function renderEmptyRows() {
    const rowsContainer = document.getElementById('guess-rows');
    rowsContainer.innerHTML = '';
    
    for (let i = 0; i < game.state.maxAttempts; i++) {
        const row = document.createElement('div');
        row.className = 'grid grid-cols-12 gap-2 w-full';
        row.id = `guess-row-${i}`;
        
        const cells = [
            { col: 'col-span-3', key: 'name' },
            { col: 'col-span-2', key: 'district' },
            { col: 'col-span-3', key: 'line' },
            { col: 'col-span-1', key: 'distance' },
            { col: 'col-span-1', key: 'transfer' },
            { col: 'col-span-2', key: 'time' },
        ];

        cells.forEach(cell => {
            const div = document.createElement('div');
            div.className = `${cell.col} h-12 border border-gray-200 rounded-lg flex items-center justify-center font-medium text-gray-400 cell`;
            div.id = `row-${i}-${cell.key}`;
            row.appendChild(div);
        });

        rowsContainer.appendChild(row);
    }
}

// 放弃当前关卡
function giveUp() {
    if (game.state.isGameOver) return;
    
    if (!confirm('确定要放弃本关吗？将直接显示答案。')) {
        return;
    }
    
    game.state.isGameOver = true;
    game.state.isWin = false;
    showResultModal();
}

// 提交猜测
function submitGuess() {
    if (game.state.isGameOver) return;
    
    const input = document.getElementById('station-input').value.trim();
    document.getElementById('station-input').value = '';
    
    if (!game.data.nameMap.has(input)) {
        alert(`该站点不存在，请输入正确的${game.data.city}地铁站名`);
        return;
    }

    const guessId = game.data.nameMap.get(input);
    const guessStation = game.data.stations.find(s => s.id === guessId);
    const answerStation = game.data.stations.find(s => s.id === game.state.answerId);
    
    const guessResult = {
        id: guessId,
        name: guessStation.name,
        districtStatus: getMatchStatus(guessStation.district, answerStation.district),
        districtText: guessStation.district.map(d => game.data.districts[d]).join('/'),
        lineStatus: getMatchStatus(guessStation.lines, answerStation.lines),
        lineText: guessStation.lines.map(l => game.data.lines[l]).join('/'),
        distance: game.distanceCache.station.get(guessId) || 0,
        transfer: Math.max(0, (game.distanceCache.transfer.get(guessId) || 0) - 1),
        timeStatus: guessStation.time === answerStation.time ? 2 : 0,
        timeText: guessStation.time,
        timeArrow: guessStation.time > answerStation.time ? '↓' : guessStation.time < answerStation.time ? '↑' : ''
    };

    game.state.guesses.push(guessResult);
    game.state.currentAttempt++;
    
    renderGuessRow(game.state.currentAttempt - 1, guessResult);
    updateGameStatus();

    if (guessId === game.state.answerId) {
        game.state.isWin = true;
        game.state.isGameOver = true;
        showResultModal();
    } else if (game.state.currentAttempt >= game.state.maxAttempts) {
        game.state.isGameOver = true;
        showResultModal();
    }
}

// 获取匹配状态
function getMatchStatus(guessArr, answerArr) {
    const guessSet = new Set(guessArr);
    const answerSet = new Set(answerArr);
    let common = 0;
    guessArr.forEach(item => {
        if (answerSet.has(item)) common++;
    });
    if (common === 0) return 0;
    if (common === answerArr.length && guessArr.length === answerArr.length) return 2;
    return 1;
}

// 渲染单条猜测行
function renderGuessRow(rowIndex, result) {
    const colorMap = {
        0: 'bg-wrong text-white border-wrong',
        1: 'bg-partial text-white border-partial',
        2: 'bg-correct text-white border-correct'
    };

    const nameCell = document.getElementById(`row-${rowIndex}-name`);
    nameCell.textContent = result.name;
    nameCell.className = `col-span-3 h-12 rounded-lg flex items-center justify-center font-medium cell flip-cell ${result.distance === 0 ? colorMap[2] : 'border border-gray-300 text-text'}`;
    nameCell.style.animationDelay = '0ms';

    const cells = [
        { key: 'district', status: result.districtStatus, text: result.districtText, delay: 100 },
        { key: 'line', status: result.lineStatus, text: result.lineText, delay: 200 },
        { key: 'distance', status: result.distance === 0 ? 2 : 0, text: result.distance, delay: 300 },
        { key: 'transfer', status: result.transfer === 0 ? 2 : 0, text: result.transfer, delay: 400 },
        { key: 'time', status: result.timeStatus, text: result.timeText + result.timeArrow, delay: 500 },
    ];

    cells.forEach(cell => {
        const el = document.getElementById(`row-${rowIndex}-${cell.key}`);
        el.textContent = cell.text;
        el.className = `${el.className.split(' ')[0]} h-12 rounded-lg flex items-center justify-center font-medium cell flip-cell ${colorMap[cell.status]}`;
        el.style.animationDelay = `${cell.delay}ms`;
    });
}

// 更新游戏状态UI
function updateGameStatus() {
    document.getElementById('guess-count').textContent = `${game.state.currentAttempt}/${game.state.maxAttempts}`;
    document.getElementById('submit-btn').disabled = game.state.isGameOver;
    document.getElementById('giveup-btn').disabled = game.state.isGameOver;
    
    document.querySelectorAll('[id^="mode-"]').forEach(btn => {
        btn.classList.remove('text-primary', 'font-semibold');
    });
    document.getElementById(`mode-${game.mode}`).classList.add('text-primary', 'font-semibold');
}

// 绑定弹窗按钮事件
function bindModalEvents() {
    document.getElementById('modal-next-level').addEventListener('click', goNextLevel);
    document.getElementById('modal-retry-level').addEventListener('click', retryCurrentLevel);
    document.getElementById('modal-restart-challenge').addEventListener('click', () => {
        initChallengeMode(true);
        document.getElementById('result-modal').classList.add('hidden');
    });
    document.getElementById('modal-retry-free').addEventListener('click', () => {
        if (game.mode === 'free') {
            const randomIndex = Math.floor(Math.random() * game.data.stations.length);
            game.state.answerId = game.data.stations[randomIndex].id;
        }
        resetGameState();
        document.getElementById('result-modal').classList.add('hidden');
    });
    document.getElementById('modal-close').addEventListener('click', () => {
        document.getElementById('result-modal').classList.add('hidden');
    });
}

// 显示结果弹窗
function showResultModal() {
    const modal = document.getElementById('result-modal');
    const answerStation = game.data.stations.find(s => s.id === game.state.answerId);
    
    document.getElementById('modal-answer').textContent = answerStation.name;
    document.getElementById('modal-guess-count').textContent = game.state.currentAttempt;

    if (game.mode === 'challenge') {
        document.getElementById('modal-next-level').classList.remove('hidden');
        document.getElementById('modal-retry-level').classList.remove('hidden');
        document.getElementById('modal-restart-challenge').classList.remove('hidden');
        document.getElementById('modal-retry-free').classList.add('hidden');
        document.getElementById('modal-close').classList.add('hidden');

        if (game.state.isWin) {
            document.getElementById('modal-title').textContent = '恭喜通关本关🎉';
            document.getElementById('modal-retry-level').classList.add('hidden');
        } else {
            document.getElementById('modal-title').textContent = '闯关失败😥';
            document.getElementById('modal-next-level').classList.add('hidden');
        }
    } else {
        document.getElementById('modal-next-level').classList.add('hidden');
        document.getElementById('modal-retry-level').classList.add('hidden');
        document.getElementById('modal-restart-challenge').classList.add('hidden');
        document.getElementById('modal-retry-free').classList.remove('hidden');
        document.getElementById('modal-close').classList.remove('hidden');

        if (game.state.isWin) {
            document.getElementById('modal-title').textContent = '恭喜你！猜对了🎉';
        } else {
            document.getElementById('modal-title').textContent = '挑战失败😥';
        }
    }

    modal.classList.remove('hidden');
    
    let isKeyEnabled = false;
    setTimeout(() => {
        isKeyEnabled = true;
    }, 1000);
    
    function handleEnterKey(e) {
        if (e.key === 'Enter' && isKeyEnabled) {
            if (game.mode === 'challenge') {
                if (game.state.isWin) {
                    goNextLevel();
                } else {
                    retryCurrentLevel();
                }
            } else {
                if (game.state.isWin) {
                    document.getElementById('modal-retry-free').click();
                } else {
                    document.getElementById('modal-close').click();
                }
            }
            document.removeEventListener('keydown', handleEnterKey);
        }
    }
    
    document.addEventListener('keydown', handleEnterKey);
}

// 全部通关弹窗
function showAllClearModal() {
    const modal = document.getElementById('result-modal');
    
    document.getElementById('modal-title').textContent = '🎉 恭喜全部通关！';
    document.getElementById('modal-desc').textContent = `你已完成${game.data.city}全部 ${game.challenge.levelList.length} 个关卡的挑战！`;
    document.getElementById('modal-stats').innerHTML = `
        <p>最后一关用了 <span class="font-semibold">${game.state.currentAttempt}</span> 次猜测</p>
        <p class="text-sm text-gray-500 mt-1">可重新开始挑战新的关卡顺序，或切换其他城市继续挑战</p>
    `;
    
    document.getElementById('modal-next-level').classList.add('hidden');
    document.getElementById('modal-retry-level').classList.add('hidden');
    document.getElementById('modal-retry-free').classList.add('hidden');
    document.getElementById('modal-close').classList.add('hidden');
    document.getElementById('modal-restart-challenge').classList.remove('hidden');

    modal.classList.remove('hidden');
    const storageKey = `metro_challenge_progress_${game.currentCity}`;
    localStorage.removeItem(storageKey);
    
    let isKeyEnabled = false;
    setTimeout(() => {
        isKeyEnabled = true;
    }, 1000);
    
    function handleEnterKey(e) {
        if (e.key === 'Enter' && isKeyEnabled) {
            document.getElementById('modal-restart-challenge').click();
            document.removeEventListener('keydown', handleEnterKey);
        }
    }
    
    document.addEventListener('keydown', handleEnterKey);
}

// 模式切换
function switchMode(mode) {
    game.mode = mode;
    document.getElementById('station-input').value = '';
    
    if (mode === 'challenge') {
        initChallengeMode();
    } else if (mode === 'free') {
        const randomIndex = Math.floor(Math.random() * game.data.stations.length);
        game.state.answerId = game.data.stations[randomIndex].id;
        resetGameState();
        document.getElementById('level-desc').textContent = '自由模式 - 猜出隐藏地铁站';
        document.getElementById('level-progress').textContent = '无限挑战';
    } else if (mode === 'custom') {
        const customName = prompt(`请输入${game.data.city}目标地铁站名：`);
        if (!customName || !game.data.nameMap.has(customName)) {
            alert('站点不存在，切换回闯关模式');
            switchMode('challenge');
            return;
        }
        const customAttempts = prompt(`请输入最大猜测次数（默认 ${game.state.maxAttempts} 次）：`, game.state.maxAttempts);
        game.state.maxAttempts = parseInt(customAttempts) || 6;
        game.state.answerId = game.data.nameMap.get(customName);
        resetGameState();
        document.getElementById('level-desc').textContent = '自定义模式 - 猜出隐藏地铁站';
        document.getElementById('level-progress').textContent = '自定义对局';
    }
}

// 页面加载初始化
window.onload = initData;

