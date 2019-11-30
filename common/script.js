(function() {

var extensions = document.createElement('div');
extensions.className = 'extensions';
var htmlSwitchContainer = document.createElement('div');
htmlSwitchContainer.className = 'html-switch';
var statisticsContainer = document.createElement('div');
statisticsContainer.className = 'statistics';
var htmlSwitch = document.createElement('input');
htmlSwitch.setAttribute('type', 'checkbox');
htmlSwitch.setAttribute('id', 'id_switch_to_html');
htmlSwitchContainer.appendChild(htmlSwitch);
var htmlSwitchLabel = document.createElement('label');
htmlSwitchLabel.setAttribute('for', 'id_switch_to_html');
htmlSwitchLabel.innerHTML = 'HTML';
htmlSwitchContainer.appendChild(htmlSwitchLabel);
var htmlCodeContainer = document.createElement('div');
htmlCodeContainer.className = 'html-code';
var htmlCodeElement = document.createElement('pre');
htmlCodeContainer.appendChild(htmlCodeElement);
var article = document.body.getElementsByTagName('article')[0];

function transformFootnotes() {
	var footnoteByName = {};
	var nextFootnoteNumber = 1;
	var footnotesElement = article.querySelector('ol.footnotes');
	var footnotesTags = Array.prototype.slice.call(article.getElementsByTagName('foot-note'));

	function createFootnote(footnoteElement) {
		if (footnotesElement === null) {
			var header = document.createElement('h2');
			header.innerHTML = 'Poznámky';
			article.appendChild(header);
			article.appendChild(document.createTextNode('\n'));
			article.appendChild(document.createTextNode('\n'));
			footnotesElement = document.createElement('ol');
			footnotesElement.className = 'footnotes';
			footnotesElement.appendChild(document.createTextNode('\n'));
			article.appendChild(footnotesElement);
		}
		var name = footnoteElement.getAttribute('name');
		var bottomFootnoteElement = footnoteByName[name];
		if (bottomFootnoteElement === undefined) {
			bottomFootnoteElement = document.createElement('li');
			bottomFootnoteElement.setAttribute('id', 'footnote-' + name);
			var link = document.createElement('a');
			link.className = 'back';
			link.setAttribute('href', '#fn-' + name);
			link.innerHTML = 'Späť';
			bottomFootnoteElement.appendChild(link);
			footnotesElement.appendChild(document.createTextNode('\t'));
			footnotesElement.appendChild(bottomFootnoteElement);
			footnotesElement.appendChild(document.createTextNode('\n'));
			footnoteByName[name] = {
				number: nextFootnoteNumber,
				element: footnoteElement
			};
			nextFootnoteNumber++;
		}
		bottomFootnoteElement.innerHTML = footnoteElement.innerHTML + bottomFootnoteElement.innerHTML;
		var footnoteInfo = footnoteByName[name];

		var inTextFootnote = document.createElement('sup');
		var inTextFootnoteLink = document.createElement('a');
		inTextFootnoteLink.setAttribute('id', 'fn-' + name);
		inTextFootnoteLink.setAttribute('href', '#footnote-' + name);
		inTextFootnoteLink.innerHTML = '['+ footnoteInfo.number +']';
		inTextFootnote.appendChild(inTextFootnoteLink);
		footnoteElement.parentNode.insertBefore(inTextFootnote, footnoteElement);
		footnoteElement.parentNode.removeChild(footnoteElement);
	}

	footnotesTags.forEach(createFootnote);
}


function transformCounters() {
	var counters = {};
	var counterTags = Array.prototype.slice.call(article.getElementsByTagName('counter'));

	function transformCounter(counterElement) {
		var name = counterElement.getAttribute('name') || 'default';
		if (counters[name] === undefined) {
			counters[name] = [0];
		}
		var counterValues = counters[name];
		counterValues[counterValues.length -1]++;

		var counterText = '';
		for (var i = 0, leni = counterValues.length; i < leni; i++) {
			counterText += counterValues[i];
			if (i < leni - 1) {
				counterText += '.';
			}
		}
		var counterTextElement = document.createTextNode(counterText);
		counterElement.parentNode.insertBefore(counterTextElement, counterElement);
		counterElement.parentNode.removeChild(counterElement);
	}

	counterTags.forEach(transformCounter);
}


function displayStatistics() {
	var paragraphs = Array.prototype.slice.call(article.getElementsByTagName('p'));
	var contents = Array.prototype.slice.call(article.querySelectorAll('p, h1, h2, h3, h4, h5, h6'));
	var charsCount = 0;
	var wordsCount = 0;
	var sentencesCount = 0;
	var paragraphsCount = paragraphs.length;

	contents.forEach(function(paragraph) {
		var text = paragraph.textContent;
		text = text.replace(/\s+/g, ' ').replace(/^s+|\s+$/, '');
		charsCount += text.length;
		if (text.length > 0) {
			wordsCount += text.split(' ').length;
			sentencesCount += text.split(/(\.|\?|\!|\:)\s+/).length;
		}
	});

	statisticsContainer.innerHTML = 'Znakov: ' + charsCount + '<br />' + 'Slov: ' + wordsCount + '<br />' + 'Viet: ' + sentencesCount + '<br />' +  'Odstavcov: ' + paragraphsCount;
}


transformFootnotes();
transformCounters();
displayStatistics();
extensions.appendChild(htmlSwitchContainer);
extensions.appendChild(statisticsContainer);
extensions.appendChild(htmlCodeContainer);
document.body.appendChild(extensions);

function escapeHtml(htmlCode) {
	return htmlCode
		.replace(/&/g, "&amp;")
		.replace(/</g, "&lt;")
		.replace(/>/g, "&gt;")
		.replace(/"/g, "&quot;")
		.replace(/'/g, "&#039;");
}

function onHtmlSwitchChanged() {
	if (htmlSwitch.checked) {
		htmlCodeElement.innerHTML = escapeHtml(article.innerHTML);
		article.style.display = 'none';
		htmlCodeContainer.style.display = 'block';
	}
	else {
		htmlCodeContainer.style.display = 'none';
		article.style.display = 'block';
	}
}

htmlSwitch.addEventListener('change', onHtmlSwitchChanged, true);
onHtmlSwitchChanged();

}());
