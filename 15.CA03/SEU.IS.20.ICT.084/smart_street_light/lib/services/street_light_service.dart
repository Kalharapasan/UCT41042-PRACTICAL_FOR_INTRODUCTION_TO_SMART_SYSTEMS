import 'package:supabase_flutter/supabase_flutter.dart';
import '../models/street_light_log.dart';

class StreetLightService {
  final SupabaseClient _client = Supabase.instance.client;

  /// Fetches the single most-recent log entry.
  Future<StreetLightLog?> fetchLatest() async {
    try {
      final response = await _client
          .from('street_light_logs')
          .select()
          .order('created_at', ascending: false)
          .limit(1)
          .maybeSingle();

      if (response == null) return null;
      return StreetLightLog.fromJson(response);
    } on PostgrestException catch (e) {
      throw Exception('Database error: ${e.message}');
    } catch (e) {
      throw Exception('Unexpected error: $e');
    }
  }

  /// Fetches the last [limit] log entries (newest first).
  Future<List<StreetLightLog>> fetchHistory({int limit = 10}) async {
    try {
      final response = await _client
          .from('street_light_logs')
          .select()
          .order('created_at', ascending: false)
          .limit(limit);

      return (response as List)
          .map((json) => StreetLightLog.fromJson(json))
          .toList();
    } on PostgrestException catch (e) {
      throw Exception('Database error: ${e.message}');
    } catch (e) {
      throw Exception('Unexpected error: $e');
    }
  }

  /// Returns a real-time stream of inserts on the table.
  Stream<StreetLightLog> realtimeStream() {
    return _client
        .from('street_light_logs')
        .stream(primaryKey: ['id'])
        .order('created_at', ascending: false)
        .limit(1)
        .map((rows) => StreetLightLog.fromJson(rows.first));
  }
}
