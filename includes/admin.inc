<?php
/**
 * Building table that contains all
 * the filled in custom labels
 *
 * @param array $variables
 */
function theme_flat_lang_autocomplete_admin_table(&$variables) {

    $form = $variables['form'];
    $rows = [];

    foreach (element_children($form['labels']) as $id) {

        $rows[] = [

            ['data' => drupal_render($form['labels'][$id]['code_render']),  'class' => 'flat-lang-autocomplete-code'],
            ['data' => drupal_render($form['labels'][$id]['code']),         'class' => 'flat-lang-autocomplete-code-hidden'],
            ['data' => drupal_render($form['labels'][$id]['label_render']), 'class' => 'flat-lang-autocomplete-label'],
            ['data' => drupal_render($form['labels'][$id]['label']),        'class' => 'flat-lang-autocomplete-label-hidden'],
            ['data' => drupal_render($form['labels'][$id]['operations']),   'class' => 'flat-lang-autocomplete-operations'],
        ];
    }

    $header = [

        ['data' => 'ISO-639-3 CODE', 'colspan' => 2, 'class' => 'flat-lang-autocomplete-code-render-header'],
        ['data' => 'LABEL',          'colspan' => 2, 'class' => 'flat-lang-autocomplete-label-render-header'],
        ['data' => 'OPERATIONS',     'colspan' => 1, 'class' => 'flat-lang-autocomplete-operations-render-header'],
    ];

    $controls   = [[

        'data'        => [['data' => drupal_render($form['add_label']), 'colspan' => 5]],
        'class'       => ['add-item-controls'],
        'no_striping' => 1,
    ]];

    $output = theme('table', [

        'header'     => $header,
        'rows'       => $rows,
        'attributes' => [

            'id'    => 'flat-lang-autocomplete-overview',
            'class' => ['flat-lang-autocomplete-labels-table']
        ]
    ]);

    $output .= theme('table', [

        'header'     => [],
        'rows'       => $controls,
        'attributes' => ['class' => ['flat-lang-autocomplete-labels-table-controls']],
    ]);

    return $output;
}
