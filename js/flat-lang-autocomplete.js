(function(jq) {

    jq.fn.FlatLangAutocomplete = function(data, filter) {

        var search  = new RegExp('.*' + filter + '.*', 'gi');
        var results = [];
        var i       = 0;

        data.forEach(function(item) {

            var terms = item.terms.filter(function(term) {
                return term.match(search);
            });

            if (terms.length > 0) {

                terms.forEach(function(term) {

                    if (i < 50) {
                        results.push({code: item.code, term: term});
                    }

                    i += 1;
                });
            }
        });

        return results;
    };

    jq(function() {

        jq('body').on('keyup', '[data-role="flat-lang-autocomplete"]', function(event) {

            // setting up variables
            var el       = jq(this);
            var dropdown = el.parent().next('div.dropdown');

            if (event.which === 27 || el.val().length < 3) {

                // cancelling search
                dropdown.remove();
                return;
            }

            // filtering data
            var results = jq.fn.FlatLangAutocomplete(Drupal.settings.flat_lang_autocomplete.languages, this.value).slice(0, 50);
            var list    = '';

            if (jQuery.trim(this.value) === '' || results.length === 0) {

                // if no text is filled in or no results found
                // remove dropdown and exit function
                dropdown.remove();
                return;
            }

            if (jq.inArray(event.which, [38, 40]) > -1) {

                // refetch dropdown to get DOM reference
                dropdown = el.parent().parent().next('div.dropdown');

                if (dropdown.find('li.active').length === 0) {

                    // no active items yet
                    // make first one active
                    dropdown.find('li:first').addClass('active');

                } else {

                    if (event.which === 38 && dropdown.find('li.active').prev().length > 0) {

                        // arrow 'up' pressed
                        // remove active class from current item
                        // and add active class to previous item
                        dropdown.find('li.active').removeClass('active').prev('li').addClass('active');
                    }

                    if (event.which === 40 && dropdown.find('li.active').next().length > 0) {

                        // arrow 'down' pressed
                        // remove active class from current item
                        // and add active class to next item
                        dropdown.find('li.active').removeClass('active').next('li').addClass('active');
                    }
                }

                return;
            }

            // building autocomplete list
            for (var i in results) {
                list += '<li><a href="#" data-code="' + results[i].code + '" data-label="' + results[i].term + '">' + results[i].term + ' (' + results[i].code + ')</a></li>';
            }

            if (dropdown.length > 0) {

                // if dropdown already exists in html
                // just replace contents with new autocomplete
                dropdown.find('ul.dropdown-menu').html(list);

            } else {

                // rebuilding dropdown
                // and adding the autocomplete results
                dropdown = jq('<div class="dropdown">' +
                                '<ul class="dropdown-menu" style="display: block; right: 0;">' +
                                    list +
                                '</ul>' +
                            '</div>');

                dropdown.insertAfter(el.parent()).on('click', 'ul li a', function(event) {

                    // preventing the link from continuing
                    event.preventDefault();

                    // if someone clicks on a result, add the result to the textfields
                    // and remove dropdown menu from DOM
                    var dropdownEl   = jq(this);
                    var destination  = el.parent().parent().parent().find('[data-role="flat-lang-autocomplete-destination"]');
                    var ignorePrefix = destination.data('flat-lang-autocomplete-ignore-prefix');

                    el.val(dropdownEl.data('label'));
                    destination.val((true === ignorePrefix ? '' : 'ISO639-3:') + dropdownEl.data('code'));

                    dropdown.remove();
                });
            }
        });
    });

})(jQuery);
