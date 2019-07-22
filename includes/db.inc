<?php
// defining labels db table name
define('FLAT_LANG_AUTOCOMPLETE_LABELS_DB', 'flat_lang_autocomplete_labels');

/**
 * db error was found, send drupal message to show what
 * went wrong
 *
 * @param Exception $e
 */
function flat_lang_autocomplete_db_error(Exception $e) {

    if ($e->errorInfo[0] == '42P01') {
        drupal_set_message(t('Flat Language Autocomplete custom labels table not found. Try running <a href="@update_url">update.php</a>.', ['@update_url' => url('update.php')]), 'error');
    } else {
        drupal_set_message($e->getMessage(), 'error');
    }
}

/**
 * Query db to fetch all the custom labels
 *
 * @return array
 */
function flat_lang_autocomplete_db_get_labels() {

    $query = db_select(FLAT_LANG_AUTOCOMPLETE_LABELS_DB, 'flal');
    $query->fields('flal');

    try {

        $result  = $query->execute();
        $data    = $result->fetchAll(PDO::FETCH_ASSOC);
        $records = [];

        foreach ($data as $item) {
            $records[$item['id']] = $item;
        }

    } catch (Exception $e) {

        flat_lang_autocomplete_db_error($e);
        $records = [];
    }

    return $records;
}

/**
 * Commit new custom labels to db
 * WARNING: this will clear the old values to commit the new ones
 *
 * @param array $labels
 *
 * @return boolean
 */
function flat_lang_autocomplete_db_commit_labels($labels) {

    $error = false;

    // purge labels
    db_delete(FLAT_LANG_AUTOCOMPLETE_LABELS_DB)->execute();

    if (count($labels) > 0) {

        $insert = db_insert(FLAT_LANG_AUTOCOMPLETE_LABELS_DB)->fields([
            'code',
            'label',
        ]);

        foreach ($labels as $code => $label) {

            $insert->values([

                'code'  => $code,
                'label' => $label,
            ]);
        }

        try {
            $insert->execute();
        } catch (Exception $e) {

            flat_lang_autocomplete_db_error($e);
            $error = true;
        }
    }

    return $error;
}
