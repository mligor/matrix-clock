import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { WifiConfigComponent } from './wifi-config/wifi-config.component';
import { MatrixClockDashboardComponent } from './matrix-clock-dashboard/matrix-clock-dashboard.component';

const routes: Routes = [
	{ path: 'dashboard', component: MatrixClockDashboardComponent },
	{ path: 'wifi-config', component: WifiConfigComponent },

	{ path: '**', redirectTo: 'dashboard' }

];

@NgModule({
	imports: [RouterModule.forRoot(routes, { useHash: false })],
	exports: [RouterModule]
})
export class AppRoutingModule { }
